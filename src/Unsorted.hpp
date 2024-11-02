#pragma once
#include <string>
#include <list>
#include <QStringList>
#include "ProgramConstants.hpp"

namespace Unsorted
{
    /// @brief Returns list QStringList of QString as element by converting std::list<std::string>value.
    QStringList STDStringListToQStringList(const std::list<std::string>& srcList);
    /// @brief Returns list std::list of std::string as element by converting QStringList<QString> value.
    inline std::list<std::string> QStringListToSTDStringList(const QStringList&            srcList);
    /// @brief Return short language name text equivalent of the enum Languages value.
    const QString GetLanguageShortName(Languages language);
    /// @brief Return full language name text equivalent of the enum Languages value.
    const QString GetLanguageFullName(Languages language);
    /// @brief Return enum Languages value that equivalent to the text value.
    inline Languages     GetLangEnumByLocale(const QString& locale);
    /// @brief Return enum Languages value that equivalent to the text value.
    Languages GetLangEnumByLocale(const std::string& locale);
    /// @brief Converts QChar to Qt::Key enum equivalent.
    Qt::Key ToQtKey(const QChar& ch);
}
