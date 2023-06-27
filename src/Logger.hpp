#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

class Logger
{
public:
    static inline Logger* Instance;
private:
    string LogFilePath;
    ofstream LogFile;

private:
    Logger();
public:
    Logger(const string& logFilePath);
    ~Logger();
    
    ofstream&& GetStream();
    string GetCurrentTime();

    void Log(stringstream const& msg);
    void Log(string const& msg);
    void Log(char* msg);
    void Log(char msg);

    void Log(wstringstream const& msg);
    void Log(wstring const& msg);
    void Log(wchar_t* msg);
    void Log(wchar_t msg);
};

ofstream operator << (Logger* pLogger, stringstream const& msg);
ofstream operator << (Logger* pLogger, string msg);
ofstream operator << (Logger* pLogger, wstringstream const& msg);
ofstream operator << (Logger* pLogger, wstring msg);
