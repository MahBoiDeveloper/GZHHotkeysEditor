#pragma once
#include <QString>

class Config
{
public:
	enum class Games {
		GENERALS = 0,
		GENERALS_ZERO_HOUR = 1
	};

	enum class Languages {
		English = 0,
		Russian = 1
	};

	static QString gameEnumToString(const Games& game);
	static QString langEnumToString(const Languages& lang);
};
