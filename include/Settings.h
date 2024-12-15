#pragma once
#include "Utils.h"

struct Feature {
	bool enabled = true;
	operator bool() const { return enabled; };

	void to_json(rapidjson::Value& j, rapidjson::Document::AllocatorType& a) const;

    void from_json(const rapidjson::Value& j);
};

namespace Settings {

	using namespace rapidjson;

	const std::uint32_t kDataKey = 'HQIM';
    const std::string path = std::format("Data/SKSE/Plugins/{}/Settings.json", Utilities::mod_name);
	
	namespace Menus {
        inline Feature container;
        inline Feature inventory;

		Feature* MenuName2Feature(std::string_view menu_name);

		rapidjson::Value to_json(Document::AllocatorType& a);
        void from_json(const rapidjson::Value& j);
	};

	void SaveSettings();
	void LoadSettings();
    void LoadDefaults();

};