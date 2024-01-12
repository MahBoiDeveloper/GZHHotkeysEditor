#include "Unsorted.hpp"
using namespace std;

namespace Unsorted
{
    /// @brief Returns list QStringList of QString as element by converting std::list<std::string>value
    QStringList STDStringListToQStringList(const list<string>& srcList)
    {
        QStringList retList;

        for (const auto& elem : srcList)
            retList.push_back(QString::fromStdString(elem));

        return retList;
    }

    /// @brief Returns list std::list of std::string as element by converting QStringList<QString> value
    list<string> QStringListToSTDStringList(const QStringList& srcList)
    {
        list<string> retList;
    
        for (const auto& elem : srcList)
            retList.push_back(elem.toStdString());
    
        return retList;
    }
}
