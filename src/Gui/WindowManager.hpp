#pragma once
#include <memory>
#include "StackedLaunchWidget.hpp"
#include "HotkeysMainWindow.hpp"

class WindowManager final
{
private: // Data
    std::unique_ptr<StackedLaunchWidget> pLaunchWidget = nullptr;
    std::unique_ptr<HotkeysMainWindow>   pHotkeysEditor = nullptr;
    QString WindowName;

public: // Methods
    WindowManager();
    void Show();
};
