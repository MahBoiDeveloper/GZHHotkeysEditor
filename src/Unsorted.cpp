#include "Unsorted.hpp"
using namespace std;

namespace Unsorted
{
    QStringList STDStringListToQStringList(const list<string>& srcList)
    {
        QStringList retList;

        for (const auto& elem : srcList)
            retList.push_back(QString::fromStdString(elem));

        return retList;
    }

    list<string> QStringListToSTDStringList(const QStringList& srcList)
    {
        list<string> retList;
    
        for (const auto& elem : srcList)
            retList.push_back(elem.toStdString());
    
        return retList;
    }
}
