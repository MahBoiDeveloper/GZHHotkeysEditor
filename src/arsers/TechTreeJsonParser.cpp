#include "TechTreeJsonParser.hpp"

#include "JSONFile.hpp"
#include "../config.hpp"

#define FILE JSONFile{Config::techTreeFile}

/// @brief
std::vector<TechTreeJsonParser::FactionInfo> TechTreeJsonParser::GetFactionsInfo()
{
    std::vector<FactionInfo> tmp;

    for (const auto& elem : FILE.Query(std::string("$.TechTree")).toArray())
    {
        std::string ShortName               = elem.toObject().value("ShortName").toString().trimmed().toStdString();
        std::string DisplayName             = elem.toObject().value("DisplayName").toString().trimmed().toStdString();
        std::string DisplayNameDesctiontion = elem.toObject().value("DisplayNameDesctiontion").toString().trimmed().toStdString();
        tmp.push_back({ShortName, DisplayName, DisplayNameDesctiontion});
    }

    return tmp;
}

std::vector<Entity> TechTreeJsonParser::getFactionBuildings(const std::string& factionShortName)
{
    for (const auto& faction : FILE.Query(std::string("$.TechTree")).toArray())
    {
        if (factionShortName == faction.toObject().value("ShortName").toString().trimmed().toStdString())
        {
            return _entitiesFromJsonArray(faction.toObject().value("Buildings").toArray());
        }
    }
    return {};
}

std::vector<Entity> TechTreeJsonParser::_entitiesFromJsonArray(const QJsonArray& array)
{
    std::vector<Entity> entities;

    for (const auto & jsonEntity : array)
    {
        entities.push_back(Entity{jsonEntity.toObject().value("Name").toString().toStdString(),
                                  jsonEntity.toObject().value("IngameName").toString().toStdString(),
                                  _actionsFromJsonArray(jsonEntity.toObject().value("Actions").toArray())});
    }

    return entities;
}

std::vector<EntityAction> TechTreeJsonParser::_actionsFromJsonArray(const QJsonArray& array)
{
    std::vector<EntityAction> actions;

    for (const auto & jsonAction : array)
    {
        actions.push_back(EntityAction{jsonAction.toObject().value("Name").toString().toStdString(),
                                       jsonAction.toObject().value("CSFString").toString().toStdString()});
    }

    return actions;
}
