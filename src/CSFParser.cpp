#include "CSFParser.hpp"
#include "Logger.hpp"
#include "Exception.hpp"

using namespace std;

#pragma region ctor and dtor
    CSFParser::CSFParser(const string& filePath) : Path(filePath)
    {
        Parse();
    }
#pragma endregion

#pragma region Parsing
    /// @brief Internal of CSF file format.
    void CSFParser::Parse()
    {
        ifstream csfFile(Path, ios::binary | ios::in);

        LOGSTM() << "Attempt to read binary file \"" << Path << "\"..." << endl;

        if (csfFile.is_open())
        {
            CSFParser::ReadHeader(&csfFile);
            CSFParser::ReadBody(&csfFile);

            LOGSTM() << "File \"" << Path << "\" has been parsed; strings count : " << Table.size() << endl;
        }
        else
        {
            throw Exception(string("Bad file name; unable to open file \"" + Path + "\""));
        }

        csfFile.close();
    }

    void CSFParser::ReadHeader(ifstream* csfFile)
    {
        csfFile->read(reinterpret_cast<char*>(&Header), sizeof(Header));

        LOGSTM() << "File header data:" << endl;

        LOGSTM() << '\t' << "First 4th bytes of file header are : [" << Header.csfChars[0] 
                                                                                    << Header.csfChars[1] 
                                                                                    << Header.csfChars[2] 
                                                                                    << Header.csfChars[3] << ']' << endl;
        LOGSTM() << '\t' << "CSF file format version             : " << Header.formatVersion      << endl;
        LOGSTM() << '\t' << "Number of labels in CSF file        : " << Header.numberOfLabels     << endl;
        LOGSTM() << '\t' << "Number of strings in CSF file       : " << Header.numberOfStrings    << endl;
        LOGSTM() << '\t' << "Useless bytes, i guess?             : " << Header.uselessBytes       << endl;
        LOGSTM() << '\t' << "Language code                       : " << Header.languageCode       << endl;
    }

    void CSFParser::ReadBody(ifstream* csfFile)
    {
        uint8_t lbl[4];
        uint8_t rts[4];
        uint8_t wrts[4];

        for (uint32_t i = 0; i < Header.numberOfLabels; i++)
        {
            bool breakFlag = false;

            // Reading ' LBL' characters
            csfFile->read(reinterpret_cast<char*>(&lbl), sizeof(lbl));

            // Comparing read characters with reference string
            for (uint8_t tmp = 0; tmp < 4; tmp++)
            {
                if (lbl[tmp] != LBL[tmp])
                {
                    if (i > 0) i--;
                    breakFlag = true;
                    break;
                }
            }
         
            // Works only if 4 chars are not equal ' LBL'
            if (breakFlag) continue;
         
            // Read count of strings linked to one string label (name)
            uint32_t countOfStrings;
            csfFile->read(reinterpret_cast<char*>(&countOfStrings), sizeof(countOfStrings));

            // Read string name without \0 sign
            uint32_t labelNameLength;
            csfFile->read(reinterpret_cast<char*>(&labelNameLength), sizeof(labelNameLength));

            // Read ASCI-like string name without \0 sign
            uint8_t labelName[labelNameLength];
            csfFile->read(reinterpret_cast<char*>(&labelName), sizeof(labelName));

            // Write string name with a special method due to string name doesn't have \0 sign
            string  stringName = CharArrayToString(sizeof(labelName), reinterpret_cast<const char*>(labelName));
            wstring stringValue;
            string  extraStringValue;

            // There possible situation where exists empty strings
            if(countOfStrings != 0)
            {
                // Read string type
                uint8_t  rtsOrWrts[4];
                csfFile->read(reinterpret_cast<char*>(&rtsOrWrts), sizeof(rtsOrWrts));

                // Read string lenght
                uint32_t valueLenght;
                csfFile->read(reinterpret_cast<char*>(&valueLenght), sizeof(valueLenght));

                // Read byte-like compiled string
                wchar_t wchBufferValue[valueLenght];
                csfFile->read(reinterpret_cast<char*>(&wchBufferValue), sizeof(wchBufferValue));

                // Reverse read string
                for (int tmp = 0; tmp < valueLenght; tmp++)
                    wchBufferValue[tmp] = ~wchBufferValue[tmp];

                // Write string name with a special method due to string name doesn't have \0 sign
                stringValue = WharArrayToWstring(valueLenght, reinterpret_cast<const wchar_t*>(wchBufferValue));

                // Read extra value and do not write bcs it's useless
                if((char)rtsOrWrts[0] == 'W')
                {
                    uint32_t extraValueLength;
                    csfFile->read(reinterpret_cast<char*>(&extraValueLength), sizeof(extraValueLength));

                    uint8_t extraValue[extraValueLength];
                    csfFile->read(reinterpret_cast<char*>(&extraValue), sizeof(extraValue));
                }

                // Add CompiledString{string Name, wstring Value} to list
                Table.push_back({stringName, stringValue});
            }
        }
    }

    /// @brief Save compiled string table data to the specific file
    void CSFParser::Save(string strFileName)
    {
        ofstream csfFile{strFileName, ios::binary | ios::out};

        if(csfFile.is_open())
        {
            LOGSTM() << "Attempt to write binary file \"" << strFileName << "\"" << endl;

            CSFParser::WriteHeader(&csfFile);
            CSFParser::WriteBody(&csfFile);

            LOGSTM() << "File saved as \"" << strFileName << "\"" << endl;
        }
        else
        {
            LOGSTM() << "Could not open file \"" << strFileName << "\" to save" << endl;
        }

        csfFile.close();
    }

    /// @brief Save compiled sting table data to the parsed file before
    void CSFParser::Save()
    {
        Save(Path);
    }

    void CSFParser::WriteHeader(ofstream* csfFile)
    {
        // Struct Header has the same length as the original file
        csfFile->write(reinterpret_cast<char*>(&Header), sizeof(Header));
    }

    void CSFParser::WriteBody(ofstream* csfFile)
    {
        const uint32_t ONE_STRING = 1;

        // Write normal strings
        for(const auto& elem : Table)
        {
            uint32_t labelLength  = elem.Name.size();
            uint32_t valueLength  = elem.Value.size();
            char     labelName      [labelLength];
            wchar_t  valueInversed  [valueLength];
         
            for(uint32_t i = 0; i < labelLength; i++)
                labelName[i] = elem.Name[i];

            for(uint32_t i = 0; i < valueLength; i++)
                valueInversed[i] = ~elem.Value[i];

            csfFile->write(reinterpret_cast<const char*>(LBL), sizeof(LBL));
            csfFile->write(reinterpret_cast<const char*>(&ONE_STRING), sizeof(ONE_STRING));
            csfFile->write(reinterpret_cast<char*>(&labelLength), sizeof(labelLength));
            csfFile->write(reinterpret_cast<char*>(&labelName), sizeof(labelName));

            csfFile->write(reinterpret_cast<const char*>(RTS), sizeof(RTS));
            csfFile->write(reinterpret_cast<char*>(&valueLength), sizeof(valueLength));
            csfFile->write(reinterpret_cast<char*>(&valueInversed), sizeof(valueInversed));
       }
    }
#pragma endregion

#pragma region Getters
    /// @brief Returns first string value by name match. The same string in uppercase and in lowercase aren't identical.
    wstring CSFParser::GetStringValue(const string& strName) const
    {
        wstring returnValue;

        for (const auto& elem : Table)
            if (elem.Name == strName)
            {
                returnValue = elem.Value;
                break;
            }

        return returnValue;
    }

    /// @brief Returns all string names in compiled sting table.
    list<string> CSFParser::GetStringNames() const
    {
        list<string> returnList;
       
        for (const auto& elem : Table)
            returnList.push_back(elem.Name);

        return returnList;
    }

    /// @brief Returns list of categories (substrings before ':').
    list<string> CSFParser::GetCategories() const
    {
        list<string> returnList;

        for (const auto& elem : Table)
            returnList.push_back(elem.Name.substr(0, elem.Name.find_first_of(':', 0) ));

        returnList.sort();
        returnList.unique();
        return returnList;
    }

    /// @brief Returns list of all strings in category with short name (substrings after ':').
    list<string> CSFParser::GetCategoryStrings(const string& strCategoryName) const
    {
        list<string> returnList;

        for (const auto& elem : Table)
            if (elem.Name.substr(0, elem.Name.find_first_of(':', 0)) == strCategoryName)
                returnList.push_back(elem.Name.substr(elem.Name.find_first_of(':', 0) + 1, elem.Name.size() - 1));

        returnList.sort();
        return returnList;
    }

    /// @brief Returns list of all strings in category.
    list<string> CSFParser::GetCategoryStringsWithFullNames(const string& strCategoryName) const
    {
        list<string> returnList;

        for (const auto& elem : Table)
            if (elem.Name.substr(0, elem.Name.find_first_of(':', 0)) == strCategoryName)
                returnList.push_back(elem.Name);

        returnList.sort();
        return returnList;
    }
    
    /// @brief Returns list of all strings that values contains wide character.
    list<string> CSFParser::GetStringsContainsSymbol(const wchar_t& wch) const
    {
        list<string> returnList;
       
        for (const auto& elem : Table)
            if (elem.Value.find(wch) <= elem.Value.size())
                returnList.push_back(elem.Name);

        returnList.sort();
        return returnList;
    }

    /// @brief Returns list of all strings that values contains wide character in specific category.
    list<string> CSFParser::GetStringsContainsSymbol(const wchar_t& wch, const string& strCategoryName) const
    {
        list<string> returnList;

        for (const auto& elem : Table)
            if (elem.Name.substr(0, elem.Name.find_first_of(':', 0)) == strCategoryName)
                if (elem.Value.find_first_of(wch) <= elem.Value.size())
                        returnList.push_back(elem.Name);

        returnList.sort();
        return returnList;
    }

    /// @brief Returns list of full strings data.
    list<CSFParser::CompiledString> CSFParser::GetStringsByNameList(const list<string>& lstNames) const
    {
        list<CompiledString> returnList;

        for (const auto& strName : lstNames)
            for (const auto& elem : Table)
                if (elem.Name == strName)
                {
                    returnList.push_back(elem);
                    break;
                }

        return returnList;
    }

    /// @brief Returns wide character (letter after & sign) assinged to keyboard key. 
    wchar_t CSFParser::GetHotkey(const string& strName) const
    {
        wchar_t hk = L'\0';
        size_t index = 0;

        for (const auto& elem : Table)
            if (elem.Name == strName)
                if ((index = elem.Value.find_first_of(L'&')) <= elem.Value.size())
                {
                    hk = elem.Value.at(index + 1);
                    break;
                }

        return hk;
    }

    /// @brief Returns list of data structs with string names and its keyboard key assignment.
    list<CSFParser::HotkeyAssociation> CSFParser::GetHotkeys(const list<string>& lstStringNames) const
    {
        list<HotkeyAssociation> returnList;

        for (const auto& strName : lstStringNames)
            for (const auto& elem : Table)
                if (strName == elem.Name)
                {
                    returnList.push_back({strName, CSFParser::GetHotkey(strName)});
                    break;
                }

        return returnList;
    }
#pragma endregion

#pragma region Setters
    /// @brief Searchs any match for string name and rewriting hotkey assignment for it.
    void CSFParser::SetHotkey(const string& strName, const wchar_t& wchLetter)
    {
        LOGSTM() << "Changing for string \"" << strName << "\" hotkey assingment to letter \"" << (const char)wchLetter << "\"" << endl;

        for (auto& elem : Table)
            if (elem.Name == strName)
            {
                size_t index = 0;

                index = elem.Value.find_first_of(L'&');

                if(index <= elem.Value.size())
                {
                    // If we could find something like [&F], then we just replace the letter
                    if(elem.Value[index - 1] == L'[' && elem.Value[index + 2] == L']')
                        elem.Value[index + 1] = wchLetter;

                    // If no, then we add [&wch] to begin of the value and delete & in text
                    else
                        elem.Value = elem.Value.erase(index, 1);
                }
            }
    }

    /// @brief Searchs any match for string name and rewriting its value.
    void CSFParser::SetStringValue(const string& strName, const wstring& wstrValue)
    {
        LOGSTM() << "Changing value for string \"" << strName << "\"" << endl;

        for (auto& elem : Table)
            if (elem.Name == strName)
                elem.Value = wstrValue;
    }

    /// @brief Searchs any match for string name and rewriting its value.
    void CSFParser::SetStringValue(const CompiledString& stString)
    {
        LOGSTM() << "Changing value for string \"" << stString.Name << "\"" << endl;

        for (auto& elem : Table)
            if (elem.Name == stString.Name)
                elem.Value = stString.Value;
    }

    /// @brief Searchs any match for string names and rewriting its values.
    void CSFParser::SetStringsValue(const list<CompiledString>& lstChanges)
    {
        for (const auto& elem : lstChanges)
            SetStringValue(elem);
    }
#pragma endregion

#pragma region Support methods
    /// @brief Pure function-convertor from char array to std::string.
    string CSFParser::CharArrayToString(const int& arrayLength, const char* pArray) const
    {
        stringstream ss;
       
        for(int i = 0 ; i < arrayLength; i++)
            ss << pArray[i];
    
        return ss.str();
    }
    
    /// @brief Pure function-convertor from wchar_t array to std::wstring.
    wstring CSFParser::WharArrayToWstring(const int& arrayLength, const wchar_t* pArray) const
    {
        wstringstream wss;
       
        for(int i = 0 ; i < arrayLength; i++)
            wss << pArray[i];
    
        return wss.str();
    }
#pragma endregion
