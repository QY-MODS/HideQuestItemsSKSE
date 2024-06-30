#pragma once
#include "Manager.h"

class OurEventSink : public RE::BSTEventSink<RE::MenuOpenCloseEvent>{
    OurEventSink() = default;
    OurEventSink(const OurEventSink&) = delete;
    OurEventSink(OurEventSink&&) = delete;
    OurEventSink& operator=(const OurEventSink&) = delete;
    OurEventSink& operator=(OurEventSink&&) = delete;

public:
    static OurEventSink* GetSingleton() {
        static OurEventSink singleton;
        return &singleton;
    }

    Manager* M = Manager::GetSingleton();

    virtual RE::BSEventNotifyControl ProcessEvent(const RE::MenuOpenCloseEvent* event,
                                                  RE::BSTEventSource<RE::MenuOpenCloseEvent>*) override;
    
};