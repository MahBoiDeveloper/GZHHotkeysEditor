#pragma once
#include <QSet>

class Settings final
{
private: // Data
    QSet<Qt::Key> allowedKeys    = {};
    bool          enabledConsole = false;

public: // Method
    Settings();
    ~Settings();

    /// @brief Set all `Settings` class variables to default values.
    void SetToDefault();
    /// @brief Parse `Resources\Settings.json`.
    void ParseSettings();

    /// @brief Returns field status for console from settings file.
    const bool IsConsoleEnabled();
    /// @brief Returns `QSet` of available keys from `QWEWRTY` keyboard to choice by user.
    const QSet<Qt::Key> GetAllowedKeys();
};
