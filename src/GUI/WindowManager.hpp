#pragma once
#include <memory>
#include <QTranslator>

#include "../ProgramConstants.hpp"

#include "LaunchWidget.hpp"
#include "HotkeysMainWindow.hpp"

#define WINDOW_MANAGER WindowManager::Instance

class WindowManager final
{
private: // Data
    std::unique_ptr<LaunchWidget>      pLaunchWidget  = nullptr;
    std::unique_ptr<HotkeysMainWindow> pHotkeysEditor = nullptr;
    inline static QTranslator*         pAppTranslator = nullptr;
    inline static Languages            Language       = Languages::English;
    QString                            WindowName;
public:
    inline static std::unique_ptr<WindowManager> Instance = nullptr;

public: // Methods
    WindowManager();
    /// @brief Enable start widget rendering.
    void Show();
    /// @brief Set common l10n translator for the whole project by language type from enum.
    void SetTranslator(Languages language);
    /// @brief Return current language type for the editor. To set language use `SetTranslator`.
    Languages GetLanguage();
};
