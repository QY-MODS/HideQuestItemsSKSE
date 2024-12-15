#include "Hooks.h"
#include "Settings.h"
#include "Manager.h"

using namespace Hooks;

template <typename MenuType>
void MenuHook<MenuType>::InstallHook(const REL::VariantID& varID) {
    REL::Relocation<std::uintptr_t> vTable(varID);
    _ProcessMessage = vTable.write_vfunc(0x4, &MenuHook<MenuType>::ProcessMessage_Hook);
}

template<typename MenuType>
RE::UI_MESSAGE_RESULTS Hooks::MenuHook<MenuType>::ProcessMessage_Hook(RE::UIMessage & a_message)
{
    const std::string_view menu_name = MenuType::MENU_NAME;
    if (const auto* feature = Settings::Menus::MenuName2Feature(menu_name); !feature || !feature->enabled) return _ProcessMessage(this, a_message);
    if (const auto msg_type = static_cast<int>(a_message.type.get()); msg_type == 1 || msg_type == 2) {
        Manager::GetSingleton()->HideQuestItems();
    }
    else if (msg_type == 3 || msg_type == 4) {
		Manager::GetSingleton()->ShowQuestItems();
    }
	return _ProcessMessage(this, a_message);
}

void Hooks::Install()
{
    MenuHook<RE::ContainerMenu>::InstallHook(RE::VTABLE_ContainerMenu[0]);
	MenuHook<RE::InventoryMenu>::InstallHook(RE::VTABLE_InventoryMenu[0]);
}
