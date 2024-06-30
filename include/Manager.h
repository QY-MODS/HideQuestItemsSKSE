#pragma once
#include "MCP.h"

enum DevamTamam {
	DEVAM,
	TAMAM
};

class Manager {
    void ForEachQuestItem(std::function<DevamTamam(RE::TESForm*)> a_func);
    std::map<RE::FormID, uint32_t> hidden_flags;

    // mutex
    std::mutex mutex;

public:
    Manager() { Init(); };

    static Manager* GetSingleton() {
        static Manager singleton;
        return &singleton;
    }

    void Init();
    void HideQuestItems();
    void ShowQuestItems();

};