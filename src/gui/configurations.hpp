#pragma once
#include <QString>

namespace configurations
{
	enum class Games {
		GENERALS = 0,
		GENERALS_ZERO_HOUR = 1
	};

	enum class Languages {
		English = 0,
		Russian = 1
	};

	QString langEnumToString(Languages lang);
}
