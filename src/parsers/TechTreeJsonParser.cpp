#include "TechTreeJsonParser.hpp"

#include "JSONFile.hpp"

TechTreeJsonParser::TechTreeJsonParser()
{

}

/// @brief
std::vector<TechTreeJsonParser::FactionInfo> TechTreeJsonParser::GetFactionsInfo()
{
    std::vector<FactionInfo> tmp;
    JSONFile file(std::string("Resources\\TechTree.json"));

    for (const auto& elem : file.Query(std::string("$.TechTree")).toArray())
    {
        std::string ShortName               = elem.toObject().value("ShortName").toString().trimmed().toStdString();
        std::string DisplayName             = elem.toObject().value("DisplayName").toString().trimmed().toStdString();
        std::string DisplayNameDesctiontion = elem.toObject().value("DisplayNameDesctiontion").toString().trimmed().toStdString();
        tmp.push_back({ShortName, DisplayName, DisplayNameDesctiontion});
    }

    return tmp;
}
