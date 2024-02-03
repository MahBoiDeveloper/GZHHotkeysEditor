#pragma once
#include <string>
#include <list>
#include <QStringList>

namespace Unsorted
{
    /// @brief Returns list QStringList of QString as element by converting std::list<std::string>value.
    QStringList            STDStringListToQStringList(const std::list<std::string>& srcList);
    /// @brief Returns list std::list of std::string as element by converting QStringList<QString> value.
    std::list<std::string> QStringListToSTDStringList(const QStringList&            srcList);
}
