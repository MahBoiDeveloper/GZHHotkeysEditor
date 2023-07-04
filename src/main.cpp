// Special C++ logic for working with strings
#include <fcntl.h> // Allows to use UTF-16 encoding as the default encoding

// Internal cute logic
#include <QApplication>
//#include <QDebug>

// Project files
#include "gui/mainwidget.hpp"
#include "Logger.hpp"
#include "Helper.hpp"
#include "CSFparser.hpp"

int main(int argc, char *argv[])
{
	// All out text MUST be showed via wcout and all chars should be converted as (wchar_t)
	_setmode(_fileno(stdout), _O_U16TEXT);

	// Define logger as the global variable
	Logger::Instance    = make_unique<Logger>("Log.log");
	Helper::Instance    = make_unique<Helper>();
	CSFparser::Instance = make_unique<CSFparser>("..\\..\\src\\csfSamples\\generalsRU.csf");

	try
	{
		Logger::Instance->Log() << "UUID: " + Helper::Instance->GetUUID();
		CSFparser::Instance->Save("CHANGED_generalsRU.csf");

		QApplication HotkeyEditor(argc, argv);
		MainWidget HotkeyEditor_Window;
		HotkeyEditor_Window.show();
		HotkeyEditor.exec();
	}
	catch(const exception& e)
	{
		Logger::Instance->Log() << "I'VE GOT A PRESENT FOR YA" << endl;
		Logger::Instance->Log(string(e.what()));
	}
	
	return 0;
}
