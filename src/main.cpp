// Special C++ logic for working with strings
#include <fcntl.h> // Allows to use UTF-16 encoding as the default encoding

// Internal cute logic
#include <QApplication>

// Project files
#include "gui/mainwidget.hpp"
#include "CSFparser.hpp"
#include "Logger.hpp"

// Don't ask me why this shit placed in main.cpp
/*
// #pragma comment(lib, "rpcrt4.lib")
// #include <Windows.h>
// string GetUUID()
// {
//     stringstream ss;

//     // Magic code by stackoverflow: https://stackoverflow.com/questions/24365331/how-can-i-generate-uuid-in-c-without-using-boost-library
//     UUID uuid;
//     auto tmpUuidCreate = UuidCreate(&uuid);
//     char* str;
//     auto tmpUuidToStringA = UuidToStringA(&uuid, (RPC_CSTR*)(&str));
//     ss << str << endl;
//     RpcStringFreeA((RPC_CSTR*)(&str));

//     return ss.str();
// }
*/

int main(int argc, char *argv[])
{
	// All out text MUST be showed via wcout and all chars should be converted as (wchar_t)
	_setmode(_fileno(stdout), _O_U16TEXT);

	// Define logger as the global variable
	Logger::Instance = make_unique<Logger>("Log.log");
	CSFparser::Instance = make_unique<CSFparser>("..\\..\\src\\csfSamples\\generalsRU.csf");

	try
	{
		// qDebug() << "!!!";
		QApplication HotkeyEditor(argc, argv);
		MainWidget HotkeyEditor_Window;
		HotkeyEditor_Window.show();
		HotkeyEditor.exec();
	}
	catch(const exception& e)
	{
		Logger::Instance->Log(e.what());
	}

	return 0;
}
