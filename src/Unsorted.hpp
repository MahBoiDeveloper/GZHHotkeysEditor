#pragma once
#include <string>
#include <list>
#include <QStringList>
#include "ProgramConstants.hpp"

namespace Unsorted
{
    /// @brief Return short language name text equivalent of the enum Languages value.
    const QString GetLanguageShortName(Languages language);
    /// @brief Return full language name text equivalent of the enum Languages value.
    const QString GetLanguageFullName(Languages language);
    /// @brief Return enum Languages value that equivalent to the text value.
    inline Languages LangEnumFromLocale(const QString& locale);
}
