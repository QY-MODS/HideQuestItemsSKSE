#include "MCP.h"
#include "Settings.h"

void MCP::Register() {
    if (!SKSEMenuFramework::IsInstalled()) {
        logger::warn("SKSE Menu Framework is not installed. Cannot register menu.");
        return;
    }
    SKSEMenuFramework::SetSection(Utilities::mod_name);
    SKSEMenuFramework::AddSectionItem("Settings", RenderSettings);
    // SKSEMenuFramework::AddSectionItem("Status", RenderStatus);
    //SKSEMenuFramework::AddSectionItem("Log", RenderLog);
}

void __stdcall MCP::RenderSettings(){
    if (ImGui::Button("Save Settings")) {
        Settings::SaveSettings();
    }

    ImGui::SameLine();

    if (ImGui::Button("Load Settings")) {
        Settings::LoadSettings();
    }

    ImGui::Checkbox("Player Inventory Menu", &Settings::Menus::inventory.enabled); 
    ImGui::Checkbox("Container Menus", &Settings::Menus::container.enabled); 
};

void HelpMarker(const char* desc) {
    ImGui::TextDisabled("(?)");
    if (ImGui::BeginItemTooltip()) {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}
