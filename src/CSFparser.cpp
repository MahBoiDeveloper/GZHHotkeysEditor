#include "CSFparser.hpp"
#include "Logger.hpp"
#include "Helper.hpp"

#pragma region ctor and dtor
    CSFparser::CSFparser(const string& filePath) : Path(filePath)
    {
        Parse();
    }
#pragma endregion

#pragma region Parsing
    void CSFparser::Parse()
    {
        ifstream csfFile(Path, ios::binary | ios::in);

        Logger::Instance->Log() << "Attempt to read binary file \"" << Path << "\"" << endl;

        if (csfFile.is_open())
        {
            CSFparser::ReadHeader(&csfFile);
            CSFparser::ReadBody(&csfFile);

            Logger::Instance->Log() << "File \"" << Path << "\" has been parsed; strings count : " << Table.size() << endl;
        }
        else
        {
            Logger::Instance->Log() << "Could not open file \"" << Path << "\" to read" << endl;
        }

        csfFile.close();
    }

    void CSFparser::ReadHeader(ifstream* csfFile)
    {
        csfFile->read(reinterpret_cast<char*>(&Header), sizeof(Header));

        Logger::Instance->Log() << "File header data:" << endl;

        Logger::Instance->Log() << '\t' << "First 4th bytes of file header are : [" << Header.csfChars[0] 
                                                                                    << Header.csfChars[1] 
                                                                                    << Header.csfChars[2] 
                                                                                    << Header.csfChars[3] << ']' << endl;
        Logger::Instance->Log() << '\t' << "CSF file format version            : "  << Header.formatVersion      << endl;
        Logger::Instance->Log() << '\t' << "Number of labels in CSF file       : "  << Header.numberOfLabels     << endl;
        Logger::Instance->Log() << '\t' << "Number of strings in CSF file      : "  << Header.numberOfStrings    << endl;
        Logger::Instance->Log() << '\t' << "Useless bytes, i guess?            : "  << Header.uselessBytes       << endl;
        Logger::Instance->Log() << '\t' << "Language code                      : "  << Header.languageCode       << endl;
    }

    void CSFparser::ReadBody(ifstream* csfFile)
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
            
            uint32_t countOfStrings;
            csfFile->read(reinterpret_cast<char*>(&countOfStrings), sizeof(countOfStrings));

            uint32_t labelNameLength;
            csfFile->read(reinterpret_cast<char*>(&labelNameLength), sizeof(labelNameLength));

            uint8_t labelName[labelNameLength];
            csfFile->read(reinterpret_cast<char*>(&labelName), sizeof(labelName));

            string  stringName = Helper::Instance->CharArrayToString(sizeof(labelName), reinterpret_cast<char*>(labelName));
            wstring stringValue = EMPTY_WSTRING;
            string  extraStringValue = EMPTY_STRING;

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

                stringValue = Helper::Instance->WharArrayToWstring(valueLenght, wchBufferValue);

                // Read extra value and do not write bcs it's useless
                if((char)rtsOrWrts[0] == 'W')
                {
                    uint32_t extraValueLength;
                    csfFile->read(reinterpret_cast<char*>(&extraValueLength), sizeof(extraValueLength));

                    uint8_t extraValue[extraValueLength];
                    csfFile->read(reinterpret_cast<char*>(&extraValue), sizeof(extraValue));

                    extraStringValue = string(reinterpret_cast<char*>(extraValue));
                }
                    
            Table.push_back({stringName, stringValue});
            }
        }
    }

    void CSFparser::Save()
    {
        ofstream csfFile{Path, ios::binary | ios::out};

        if(csfFile.is_open())
        {
            Logger::Instance->Log() << "Attempt to write binary file \"" << Path << "\"" << endl;

            CSFparser::WriteHeader(&csfFile);
            CSFparser::WriteBody(&csfFile);

            Logger::Instance->Log() << "File saved as \"" << Path << "\"" << endl;
        }
        else
        {
            Logger::Instance->Log() << "Could not open file \"" << Path << "\" to save" << endl;
        }

        csfFile.close();
    }

    void CSFparser::Save(string strFileName)
    {
        string tmp = Path;
        Path = strFileName;
        CSFparser::Save();
        Path = tmp;
    }

    void CSFparser::WriteHeader(ofstream* csfFile)
    {
        // Struct Header has the same length as the original file
        csfFile->write(reinterpret_cast<char*>(&Header), sizeof(Header));
    }

    void CSFparser::WriteBody(ofstream* csfFile)
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
    wstring CSFparser::GetStringValue(const string& strName)
    {
       for (const auto& elem : Table)
            if (elem.Name == strName)
                return elem.Value;

        return EMPTY_WSTRING;
    }

    list<string> CSFparser::GetStringNames()
    {
        list<string> returnList;
        
        for (const auto& elem : Table)
            returnList.push_back(elem.Name);

        returnList.sort();

        return returnList;
    }

    list<string> CSFparser::GetCategories()
    {
        list<string> returnList;

        for (const auto& elem : Table)
            returnList.push_back(elem.Name.substr(0, elem.Name.find_first_of(':', 0) ));

        returnList.sort();
        returnList.unique();

        return returnList;
    }

    list<string> CSFparser::GetCategoryStrings(const string& strCategoryName)
    {
        list<string> returnList;

           for (const auto& elem : Table)
            if (elem.Name.substr(0, elem.Name.find_first_of(':', 0)) == strCategoryName)
                returnList.push_back(elem.Name.substr(elem.Name.find_first_of(':', 0) + 1, elem.Name.size() - 1));

        returnList.sort();
        return returnList;
    }

    list<string> CSFparser::GetCategoryStringsWithFullNames(const string& strCategoryName)
    {
        list<string> returnList;

        for (const auto& elem : Table)
            if (elem.Name.substr(0, elem.Name.find_first_of(':', 0)) == strCategoryName)
                returnList.push_back(elem.Name);

        returnList.sort();
        return returnList;
    }
    
    list<string> CSFparser::GetStringsContainsSymbol(const wchar_t& wch)
    {
        list<string> returnList;
        
        for (const auto& elem : Table)
            if (elem.Value.find(wch) <= elem.Value.size())
                returnList.push_back(elem.Name);

        returnList.sort();

        return returnList;
    }

    list<string> CSFparser::GetStringsContainsSymbol(const wchar_t& wch, const string& strCategoryName)
    {
        list<string> returnList;

        for (const auto& elem : Table)
            if (elem.Name.substr(0, elem.Name.find_first_of(':', 0)) == strCategoryName)
                if (elem.Value.find_first_of(wch) <= elem.Value.size())
                    returnList.push_back(elem.Name);

        returnList.sort();

        return returnList;
    }

    list<CompiledString> CSFparser::GetStringsByNameList(const list<string>& lstNames)
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
#pragma endregion

#pragma region Setters
    void CSFparser::SetStringValue(const string& strName, const wstring& wstrValue)
    {
        for (auto& elem : Table)
            if (elem.Name == strName)
                elem.Value = wstrValue;
    }

    void CSFparser::SetStringValue(const CompiledString& stString)
    {
        for (auto& elem : Table)
            if (elem.Name == stString.Name)
                elem.Value = stString.Value;
    }

    void CSFparser::SetStringsValue(const list<CompiledString>& lstChanges)
    {
        for (const auto& elem : lstChanges)
            CSFparser::SetStringValue(elem);
    }
#pragma endregion
