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
    string GetCurrentTime();
public:
    Logger(const string& logFilePath);
    ~Logger();
    
    ofstream* GetStream();

    void Log(stringstream const& msg);
    void Log(string msg);
    void Log(char* msg);
    void Log(char msg);

    void Log(wstringstream const& msg);
    void Log(wstring msg);
    void Log(wchar_t* msg);
    void Log(wchar_t msg);
};
