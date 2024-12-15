#include "Manager.h"

void Manager::ForEachQuestItem(std::function<DevamTamam(RE::TESForm*)> a_func){
	const auto inventory = RE::PlayerCharacter::GetSingleton()->GetInventory();
	for (const auto& [fst, snd] : inventory) {
        if (!fst) {
			continue;
        } if (snd.first <= 0) {
			continue;
        } if (const auto* inv_data = snd.second.get(); !inv_data || inv_data->IsLeveled() || inv_data->IsWorn() ||
                                                             inv_data->IsFavorited() || !inv_data->IsQuestObject()) {
			continue;
		}
        if (const auto form = fst; a_func(form) == DevamTamam::TAMAM) {
			break;
		}
	}
};

void Manager::Init() {
	logger::info("Manager initialized"); }

void Manager::HideQuestItems() {
	// we dont want multiple threads to access hidden_flags at the same time
	std::lock_guard<std::mutex> lock(mutex);

    ForEachQuestItem([this](RE::TESForm* a_form) {
		if (a_form->formFlags!=13) {
            this->hidden_flags[a_form->formID] = a_form->formFlags;
			a_form->formFlags = 13;
		}
		return DEVAM;
	});
}

void Manager::ShowQuestItems() {
	// we dont want multiple threads to access hidden_flags at the same time
	std::lock_guard<std::mutex> lock(mutex);
    if (hidden_flags.empty()) {
		logger::trace("No quest items to show");
		return;
	}
	ForEachQuestItem([this](RE::TESForm* a_form) {
		const auto actual_flag = this->hidden_flags.contains(a_form->formID) ? this->hidden_flags.at(a_form->formID) : 9;
		if (a_form->formFlags==13) {
            a_form->formFlags = actual_flag;
		}
        hidden_flags.erase(a_form->formID);
		return DEVAM;
	});
}
