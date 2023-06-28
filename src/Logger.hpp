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
    ~Logger();
    string GetCurrentTime();
public:
    Logger(const string& logFilePath);
    void Dispose();

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
