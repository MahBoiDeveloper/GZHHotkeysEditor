#pragma once
#include <memory>
#include "LaunchWidget.hpp"
#include "HotkeysMainWindow.hpp"

class WindowManager final
{
private: // Data
    std::unique_ptr<LaunchWidget>      pLaunchWidget  = nullptr;
    std::unique_ptr<HotkeysMainWindow> pHotkeysEditor = nullptr;
    QString WindowName;

public: // Methods
    WindowManager();
    /// @brief Enable start widget rendering.
    void Show();
};
