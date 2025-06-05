#ifdef PROJECT_EXE_RELATIVE_PATH

#define EXCEPTION_HEADER "I'VE GOT A PRESENT FOR YA"
#define RESOURCES "Resources"
#define BINARIES "Resources/Binaries"

#include <vector>
#include <cstdlib>
#include <string>
#include <filesystem>
#include <iostream>

// Links local executable to the main application of the project
int main(int argc, const char** argv)
{
    // Create /Logs if they doesn't exists
    std::filesystem::create_directory("Logs");

    if (!std::filesystem::exists(RESOURCES))
    {
        std::cout << "Folder \""<< RESOURCES <<"\" doesn't exist!" << std::endl 
                  << "You cannot use Hotkey Editor without configs and Qt binary files." << std::endl
                  << "Check your installation instruction." << std::endl;
        return -1;
    }

    if (!std::filesystem::exists(BINARIES))
    {
        std::cout << "Folder \"" << BINARIES << "\" doesn't exist!" << std::endl 
                  << "You cannot use Hotkey Editor without Qt binary files." << std::endl
                  << "Check your installation instruction." << std::endl;
        return -1;
    }

    std::stringstream ss(PROJECT_EXE_RELATIVE_PATH);
    std::string tmp = "";
    const char del = '/';
    std::vector<std::string> vec;
    vec.reserve(3);

    // Split Cmake's path by / in PROJECT_EXE_RELATIVE_PATH
    while (getline(ss, tmp, del))
        vec.push_back(tmp);

    // Concat all stirng parts with \ character and excluding the last
    std::string accum = vec.at(0);
    for (int i = 1; i < vec.size() - 1; i++)
        accum += '\\' + vec.at(i);

    // Form command like `start /D "Resources\Binaries" LoadEditor.exe`
    std::string realExecutablePath = "start /D \"" + accum + "\"" + " " + vec.at(vec.size() - 1);

    // Add commands from argv. Skip first argument because it is just MainStarter.cpp .exe name
    for (int i = 1; i < argc; i++)
        realExecutablePath += " " + std::string(argv[i]);

    // Call the main executable
    return system(realExecutablePath.c_str());
}
#endif
