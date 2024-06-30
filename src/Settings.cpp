#include "Settings.h"

void Settings::SaveSettings() {
    rapidjson::Document doc;
    doc.SetObject();

    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    rapidjson::Value version(rapidjson::kObjectType);
    version.AddMember("major", Utilities::plugin_version.major(), allocator);
    version.AddMember("minor", Utilities::plugin_version.minor(), allocator);
    version.AddMember("patch", Utilities::plugin_version.patch(), allocator);
    version.AddMember("build", Utilities::plugin_version.build(), allocator);

    doc.AddMember("plugin_version", version, allocator);

    doc.AddMember("menus", Settings::Menus::to_json(allocator), allocator);

    // Convert JSON document to string
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    // Write JSON to file
    std::string filename = Settings::path;
    std::filesystem::create_directories(std::filesystem::path(filename).parent_path());
    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        logger::error("Failed to open file for writing: {}", filename);
        return;
    }
    ofs << buffer.GetString() << std::endl;
    ofs.close();
}

void Settings::LoadSettings() {
    LoadDefaults();

    std::string filename = Settings::path;

    if (!std::filesystem::exists(filename)) {
        logger::info("Settings file does not exist. Creating default settings.");
        SaveSettings();
        return;
    }

    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        logger::error("Failed to open file for reading: {}", filename);
        return;
    }

    rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document doc;
    doc.ParseStream(isw);
    if (doc.HasParseError()) {
        logger::error("Failed to parse JSON settings file: {}", filename);
        return;
    }
    if (doc.HasMember("menus")) Settings::Menus::from_json(doc["menus"]);

    ifs.close();

    logger::info("Settings loaded from file: {}", filename);
}

void Settings::LoadDefaults() {
    Settings::Menus::container.enabled = true;
    Settings::Menus::inventory.enabled = true;
};

rapidjson::Value Settings::Menus::to_json(Document::AllocatorType& a) {
    Value menus(kObjectType);

    Value container_menu(kObjectType);
    container.to_json(container_menu, a);
    menus.AddMember("container_menu", container_menu, a);
    
    Value player_inventory_menu(kObjectType);
    inventory.to_json(player_inventory_menu, a);
    menus.AddMember("player_inventory_menu", player_inventory_menu, a);

    return menus;
}

void Settings::Menus::from_json(const rapidjson::Value& j) {
    if (j.HasMember("container_menu")) container.from_json(j["container_menu"]);
    if (j.HasMember("player_inventory_menu")) inventory.from_json(j["player_inventory_menu"]);

}

void Feature::to_json(rapidjson::Value& j, rapidjson::Document::AllocatorType& a) const {
    j.AddMember("enabled", enabled, a);
    rapidjson::Value keymap_array(rapidjson::kArrayType);
}

void Feature::from_json(const rapidjson::Value& j) {
    enabled = j["enabled"].GetBool();
}
