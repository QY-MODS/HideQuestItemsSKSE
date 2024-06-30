#include "Events.h"

RE::BSEventNotifyControl OurEventSink::ProcessEvent(const RE::MenuOpenCloseEvent* event,
                                                    RE::BSTEventSource<RE::MenuOpenCloseEvent>*) {
    
    if (!event) return RE::BSEventNotifyControl::kContinue;

    bool is_inventory_menu = event->menuName == RE::InventoryMenu::MENU_NAME;
    bool is_container_menu = event->menuName == RE::ContainerMenu::MENU_NAME;

    bool hide_show = is_inventory_menu && Settings::Menus::inventory ||
                        is_container_menu && Settings::Menus::container;

    if (!hide_show) return RE::BSEventNotifyControl::kContinue;

    if (event->opening) {
        logger::trace("Menu opened: {}, hiding quest items", event->menuName);
		M->HideQuestItems();
	} else {
        logger::trace("Menu closed: {}, showing quest items", event->menuName);
		M->ShowQuestItems();
	}
    
    return RE::BSEventNotifyControl::kContinue;
}