#include <exception>
#include <fstream>

#include "JSONFile.hpp"
#include "ExceptionMessage.hpp"

using namespace std;

#pragma region ctor and dtor
    JSONFile::JSONFile(const string& filePath) : FileName{filePath}
    {
        ifstream openedFile(FileName.c_str(), ios::binary | ios::in);
        
        // Check if file opened for reading
        if (openedFile.is_open())
            openedFile.close();

        // If file doesn't exist, throw exception with error message
        else
            throw ExceptionMessage(string("Bad file name; unable to open file \"" + FileName + "\""));
    }
#pragma endregion

#pragma region Getters
    std::string JSONFile::GetValue(const std::string& strJsonPath) const
    {
        return to_string("");
    }
#pragma endregion
