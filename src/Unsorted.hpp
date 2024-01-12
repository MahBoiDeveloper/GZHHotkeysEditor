#pragma once
#include <string>
#include <list>
#include <QStringList>

namespace Unsorted
{
    QStringList            STDStringListToQStringList(const std::list<std::string>& srcList);
    std::list<std::string> QStringListToSTDStringList(const QStringList&            srcList);
}
