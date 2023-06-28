#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
using namespace std;

class Logger
{
public:
	static inline unique_ptr<Logger> Instance;
private:
    ofstream LogFile;

private:
    string GetCurrentTime();
public:
	Logger() = delete;
	Logger(const string& logFilePath);
	~Logger();
//    void Dispose();

    ofstream& Log();

    void Log(const stringstream& msg);
    void Log(const string& msg);
    void Log(char* msg);
    void Log(char msg);

    void Log(const wstringstream& msg);
    void Log(const wstring& msg);
    void Log(wchar_t* msg);
	void Log(wchar_t msg);
};
