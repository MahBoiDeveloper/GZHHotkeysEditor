#include "config.hpp"

QString Config::gameEnumToString(const Games& game)
{
	switch (game) {
	case Games::GENERALS:
		return "Generals";
		break;
	case Games::GENERALS_ZERO_HOUR:
		return "Generals Zero Hour";
		break;
	default:
		return gameEnumToString(Games::GENERALS);
		break;
	}
}

QString Config::langEnumToString(const Languages& lang)
{
	QString fileBaseName = "Gui_";
	switch (lang) {
	case Languages::English:
		return fileBaseName + "en";
		break;
	case Languages::Russian:
		return fileBaseName + "ru";
		break;
	default:
		return langEnumToString(Languages::English);
		break;
	}
}
