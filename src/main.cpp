// Special C++ logic for working with strings
#include <fcntl.h> // Allows to use UTF-16 encoding as the default encoding

// Project files
#include "gui/mainwidget.hpp"
#include "CSFparser.hpp"

// Internal cute logic
#include <QApplication>

int main(int argc, char *argv[])
{
	// All out text MUST be showed via wcout and all chars should be converted as (wchar_t)
	_setmode(_fileno(stdout), _O_U16TEXT);

	// qDebug() << "!!!";
	QApplication HotkeyEditor(argc, argv);
	MainWidget HotkeyEditor_Window;
	HotkeyEditor_Window.show();
	auto tmp = new CSFparser("..\\..\\src\\csfSamples\\generalsRU.csf");
	delete(tmp);
	return HotkeyEditor.exec();
}
