#pragma once
#include <QSet>
#include "Parsers/JSONFile.hpp"

enum class Languages
{
    English,
    Russian,
    Count
};

class Settings final
{
private: // Data
    JSONFile      json;
    QSet<Qt::Key> AllowedHotkeys;
    bool          DebugConsole;
    bool          DiscordRPC;
    bool          ForceSystemLanguage;
    Languages     Language;

private: // Methods
    bool FromQtCheckState(const Qt::CheckState& state);
public:
    Settings();
    ~Settings();

    /// @brief Set all `Settings` class variables to default values.
    void SetToDefault();
    /// @brief Parse `Resources\Settings.json`.
    void Parse();
    /// @brief Save changes to the `Resources\Settings.json`.
    void Save();

    /// @brief Returns status for console from settings file.
    const bool IsConsoleEnabled() const;
    /// @brief Returns status for Discord RPC from settings file.
    const bool IsDiscordRPCEnabled() const;
    /// @brief Returns status for force editor use system language from settings file.
    const bool IsForceSystemLanguageOnStartUpEnabled() const;
    /// @brief Returns `QSet` of available keys from `QWEWRTY` keyboard to choice by user.
    const QSet<Qt::Key> GetAllowedKeys() const;
    /// @brief Returns enum `Languages` value of current language from settings file.
    const Languages GetLanguage() const;

    /// @brief Sets status for console window.
    void SetConsoleStatus(const Qt::CheckState& state);
    /// @brief Sets status for console window.
    void SetConsoleStatus(const bool state);
    /// @brief Sets `QSet` of allowed keys.
    void SetAllowedKeys(const QSet<Qt::Key>& keys);
    /// @brief Sets status for Discord RPC.
    void SetDiscordRPCStatus(const Qt::CheckState& state);
    /// @brief Sets status for Discord RPC.
    void SetDiscordRPCStatus(const bool state);
    /// @brief Sets status to force editor use system language.
    void SetForceSystemLanguageOnStartUp(const bool state);
    /// @brief Sets status to force editor use system language.
    void SetForceSystemLanguageOnStartUp(const Qt::CheckState& state);
    /// @brief Sets editor's language.
    void SetLanguage(const Languages& locale);
};
