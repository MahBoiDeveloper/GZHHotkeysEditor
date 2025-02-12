#pragma once
#include <memory>
#include <QTranslator>

#include "../ProgramConstants.hpp"
#include "../Convert.hpp"
#include "../Registry.hpp"

#include "LaunchWidget.hpp"
#include "HotkeysMainWindow.hpp"

#define WINDOW_MANAGER WindowManager::Instance

class WindowManager final
{
private: // Data
    std::unique_ptr<LaunchWidget>      pLaunchWidget      = nullptr;
    std::unique_ptr<HotkeysMainWindow> pHotkeysEditor     = nullptr;
    inline static QTranslator*         pAppTranslator     = nullptr;
    inline static Languages            Language           = Languages::English; // Convert::ToLangEnum(Registry::GetCurrentUserLanguage());
    QString                            strWindowName      = "C&C: Generals Zero Hour Hotkey Editor";
    bool                               bEditorInitialized = false;
public:
    inline static std::unique_ptr<WindowManager> Instance = nullptr;

public: // Methods
    WindowManager();
    /// @brief Enable start widget rendering.
    void Show();
    /// @brief Set common L10N translator for the whole project app by language type from enum.
    void SetTranslator(Languages language);
    /// @brief Return current language type for the editor. To set language use `SetTranslator`.
    Languages GetLanguage();
    /// @brief Due to Qt limitations this slot is a public and should be calls only in `LaunchWidget` to launch editor.
    void LaunchWidget_AcceptConfiguration(const QVariant& cfg);
};
