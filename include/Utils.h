#pragma once
#include "rapidjson/document.h"
#include <rapidjson/error/en.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include <windows.h>

#include <ClibUtil/editorID.hpp>
#include <filesystem>
#include <fstream>
#include <string>
#include "SKSEMCP/SKSEMenuFramework.hpp"

namespace Utilities {

    const auto mod_name = static_cast<std::string>(SKSE::PluginDeclaration::GetSingleton()->GetName());
    const auto plugin_version = SKSE::PluginDeclaration::GetSingleton()->GetVersion();

    //std::filesystem::path GetLogPath();

    //std::vector<std::string> ReadLogFile();

    namespace Menu {

        //bool IsOpen(const std::string_view menuname);

    };

    inline std::string formatFloatToString(float value, int precision) {
        std::ostringstream out;
        out << std::fixed << std::setprecision(precision) << value;
        return out.str();
    }

};