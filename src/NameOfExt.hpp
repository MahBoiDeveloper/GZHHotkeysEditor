#include <QString>
#include "../lib/nameof/nameof.h"
#define nameof(x) QString::fromStdString(std::string(NAMEOF(x)))
