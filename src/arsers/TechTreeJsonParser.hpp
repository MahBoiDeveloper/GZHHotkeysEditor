#pragma once

#include <entity.hpp>

#include <QJsonArray>

class TechTreeJsonParser
{

public:// Types
    struct FactionInfo
    {
        std::string ShortName;
        std::string DisplayName;
        std::string DisplayNameDesctiontion;
    };

public: // Methods
    static std::vector<FactionInfo> GetFactionsInfo();
    static std::vector<Entity> getFactionBuildings(const std::string& factionShortName);

private:
    static std::vector<Entity> _entitiesFromJsonArray(const QJsonArray& array);
    static std::vector<EntityAction> _actionsFromJsonArray(const QJsonArray& array);
    static std::vector<EntityAction> _getEntityActions(const std::string& entityName);
};
