#include <QJsonArray>
#include "Parsers/JSONFile.hpp"
#include "Logger.hpp"

#include "ProgramConstants.hpp"

ProgramConstants::ProgramConstants()
{
}

const QSet<Qt::Key> ProgramConstants::GetAllowedKeys()  { return SettingsFile->GetAllowedKeys(); }
const bool ProgramConstants::IsConsoleEnabled()         { return SettingsFile->IsConsoleEnabled(); }
void ProgramConstants::InitializeFileSettings()         { SettingsFile = std::make_unique<Settings>(); }
