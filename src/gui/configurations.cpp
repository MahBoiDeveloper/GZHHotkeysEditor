#include "configurations.hpp"

QString configurations::langEnumToString(Languages lang)
{
	QString fileBaseName = "Gui_";
	switch (lang) {
	case configurations::Languages::English:
		return fileBaseName + "en";
		break;
	case configurations::Languages::Russian:
		return fileBaseName + "ru";
		break;
	default:
		return fileBaseName + "en";
		break;
	}
}
