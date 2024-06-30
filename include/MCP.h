#pragma once
#include "Settings.h"

void HelpMarker(const char* desc);

const ImGuiTableFlags table_flags =
    ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable;

namespace MCP {

    //inline std::string log_path = Utilities::GetLogPath().string();
    //inline std::vector<std::string> logLines;

    void Register();

    void __stdcall RenderSettings();
    // void __stdcall RenderStatus();
    //void __stdcall RenderLog();


};