#pragma once
#include <memory>
#include <QTranslator>

#include "../ProgramConstants.hpp"

#include "SetUpWindowsWrapper.hpp"
#include "HotkeysMainWindow.hpp"

#define WINDOW_MANAGER WindowManager::Instance

class WindowManager final
{
private: // Data
    std::unique_ptr<SetUpWindowsWrapper> pStartUpWindow     = nullptr;
    std::unique_ptr<HotkeysMainWindow>   pHotkeysEditor     = nullptr;
    inline static QTranslator*           pAppTranslator     = nullptr;
    inline static Languages              Language           = Languages::English;
    QString                              strWindowName      = PROGRAM_CONSTANTS->COMMON_TITLE;
    bool                                 bEditorInitialized = false;
    QString                              strCSFFilePath     = "";
public:
    inline static std::unique_ptr<WindowManager> Instance   = nullptr;

public: // Methods
    WindowManager();
    /// @brief Enable start widget rendering.
    void Show();
    /// @brief Set common L10N translator for the whole project app by language type from enum.
    void SetTranslator(Languages language);
    /// @brief Return current language type for the editor. To set language use `SetTranslator`.
    Languages GetLanguage();
    /// @brief Set CSF file path. Uses if in `LoadFromTheFileWindow` file has been set.
    void SetCSFFilePath(const QString& filepath);
    /// @brief Return CSF file path. Uses if in `LoadFromTheFileWindow` file has been set.
    void LaunchWidget_AcceptConfiguration();
};
