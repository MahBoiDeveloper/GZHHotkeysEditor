#pragma once
#include <QSet>
#include "Parsers/JSONFile.hpp"

class Settings final
{
private: // Data
    QSet<Qt::Key> allowedKeys       = {};
    bool          enabledConsole    = false;
    bool          enabledDiscordRPC = false;

public: // Method
    Settings();
    ~Settings();

    /// @brief Set all `Settings` class variables to default values.
    void SetToDefault();
    /// @brief Parse `Resources\Settings.json`.
    void Parse();
    /// @brief Save changes to the `Resources\Settings.json`.
    void Save();

    /// @brief Returns field status for console from settings file.
    const bool IsConsoleEnabled() const;
    /// @brief Returns `QSet` of available keys from `QWEWRTY` keyboard to choice by user.
    const QSet<Qt::Key> GetAllowedKeys() const;
    /// @brief Returns field status for Discord RPC from settings file.
    const bool IsDiscordRPCEnabled() const;

    /// @brief Sets field status for console window.
    void SetConsoleStatus(const Qt::CheckState& state);
    /// @brief Sets field status for console window.
    void SetConsoleStatus(bool state);
    /// @brief Sets `QSet` of allowed keys.
    void SetAllowedKeys(const QSet<Qt::Key>& keys);
    /// @brief Sets field status for Discord RPC.
    void SetDiscordRPCStatus(const Qt::CheckState& state);
    /// @brief Sets field status for Discord RPC.
    void SetDiscordRPCStatus(bool state);
};
