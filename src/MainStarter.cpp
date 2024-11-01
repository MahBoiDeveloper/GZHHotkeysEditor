#ifdef PROJECT_EXE_RELATIVE_PATH

#define EXCEPTION_HEADER "I'VE GOT A PRESENT FOR YA"
#define RESOURCES "Resources"
#define BINARIES "Resources\\Binaries"

#include <cstdlib>
#include <string>
#include <filesystem>
#include <iostream>
// #include <QMessageBox>

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
        // QMessageBox::critical(nullptr, EXCEPTION_HEADER, "Folder \"Resources\" is empty!\n Checkout installation instruction.");
        return -1;
    }

    if (!std::filesystem::exists(BINARIES))
    {
        std::cout << "Folder \"" << BINARIES << "\" doesn't exist!" << std::endl 
                  << "You cannot use Hotkey Editor without Qt binary files." << std::endl
                  << "Check your installation instruction." << std::endl;
        // QMessageBox::critical(nullptr, EXCEPTION_HEADER, "Folder \"Resources\" is empty!\n Checkout installation instruction.");
        return -1;
    }
    
    std::string realExecutablePath(PROJECT_EXE_RELATIVE_PATH);

    // Replace the forward slash with the reverse slash
    size_t pos = 0;

    // Replace Cmake's path with '/' to '\\'
    while ((pos = realExecutablePath.find('/',pos)) != std::string::npos)
        realExecutablePath.replace(pos++, 1, "\\\\");

    // Add commands from argv. Skip first argument because it is just MainStarter.cpp .exe name
    for (int i = 1; i < argc; i++)
        realExecutablePath += std::string(" ") + std::string(argv[i]);

    // Call the main executable
    return system(realExecutablePath.c_str());
}
#endif

