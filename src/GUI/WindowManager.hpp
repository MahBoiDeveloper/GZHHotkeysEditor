#pragma once
#include <QTranslator>

#include "../ProgramConstants.hpp"

#include "SetUpWindowsWrapper.hpp"
#include "EditorWindow.hpp"

#define WINDOW_MANAGER WindowManager::Instance

class WindowManager final
{
private: // Data
    SetUpWindowsWrapper* pStartUpWindow = nullptr;
    EditorWindow*        pHotkeysEditor = nullptr;
    QTranslator*         pAppTranslator = nullptr;
    QString              strWindowName  = PROGRAM_CONSTANTS->COMMON_TITLE;
    QString              strCSFFilePath = "";
public:
    inline static std::unique_ptr<WindowManager> Instance   = nullptr;

public: // Methods
    WindowManager();
    ~WindowManager();
    /// @brief Enable start widget rendering.
    void Show();
    /// @brief Set common L10N translator for the whole project app.
    void SetTranslator();
    /// @brief Set CSF file path. Uses if in `LoadFromTheFileWindow` file has been set.
    void SetCSFFilePath(const QString& filepath);
    /// @brief Return CSF file path. Uses if in `LoadFromTheFileWindow` file has been set.
    void StartUpWindow_AcceptConfiguration();
};
