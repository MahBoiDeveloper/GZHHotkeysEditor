#include "CSFparser.hpp"
#include "Logger.hpp"

#pragma region Initialization and finilization
    CSFparser::CSFparser(const string& filePath) : Path(filePath)
    {
        pTable = new list<CompiledString>();
        Parse();
        
        Logger::Instance->Log() << "File has been parsed; strings count : " << pTable->size() << endl;
    }

    CSFparser::~CSFparser()
    {
        delete pTable;
    }
#pragma endregion

#pragma region Parsing
    inline void CSFparser::Parse()
    {
        ifstream csfFile{Path, ios::binary | ios::in};

        Logger::Instance->Log() << "Attempt to read binary file \"" << Path << "\"" << endl;

        if (csfFile.is_open())
        {
            CSFparser::ReadHeader(&csfFile);
            CSFparser::ReadBody(&csfFile);

            Logger::Instance->Log() << "File \"" << Path << "\" has been parsed" << endl;
        }
        else
        {
            Logger::Instance->Log() << "Could not open file \"" << Path << "\" to read" << endl;
        }

        csfFile.close();
    }

    inline void CSFparser::ReadHeader(ifstream* csfFile)
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

    inline void CSFparser::ReadBody(ifstream* csfFile)
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

            string  stringName = CSFparser::CharArrayToString(sizeof(labelName), reinterpret_cast<char*>(labelName));
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
                wchar_t _stringValue[valueLenght];
                csfFile->read(reinterpret_cast<char*>(&_stringValue), sizeof(_stringValue));

                // Reverse read string
                for (int tmp = 0; tmp < valueLenght; tmp++)
                    _stringValue[tmp] = ~_stringValue[tmp];

                stringValue = WharArrayToWstring(valueLenght, _stringValue);

                // Read extra value and do not write bcs it's useless
                if((char)rtsOrWrts[0] == 'W')
                {
                    uint32_t extraValueLength;
                    csfFile->read(reinterpret_cast<char*>(&extraValueLength), sizeof(extraValueLength));

                    uint8_t extraValue[extraValueLength];
                    csfFile->read(reinterpret_cast<char*>(&extraValue), sizeof(extraValue));

                    extraStringValue = CSFparser::CharArrayToString(sizeof(extraValue), reinterpret_cast<char*>(extraValue));
                }
                    
                pTable->push_back({stringName, stringValue});
            }
            
            #if DEBUG
            wcout << "Name   : [" << stringName.c_str()       << "]" << endl;
            wcout << "String : [" << stringValue              << "]" << endl;
            wcout << "Extra  : [" << extraStringValue.c_str() << "]" << endl << endl;
            #endif
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

    inline void CSFparser::WriteHeader(ofstream* csfFile)
    {
        // Struct Header has the same length as the original file
        csfFile->write(reinterpret_cast<char*>(&Header), sizeof(Header));
    }

    inline void CSFparser::WriteBody(ofstream* csfFile)
    {
        uint32_t one = 1;

        // Write normal strings
        for(auto elem : *pTable)
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
            csfFile->write(reinterpret_cast<char*>(&one), sizeof(one));
            csfFile->write(reinterpret_cast<char*>(&labelLength), sizeof(labelLength));
            csfFile->write(reinterpret_cast<char*>(&labelName), sizeof(labelName));

            csfFile->write(reinterpret_cast<const char*>(RTS), sizeof(RTS));
            csfFile->write(reinterpret_cast<char*>(&valueLength), sizeof(valueLength));
            csfFile->write(reinterpret_cast<char*>(&valueInversed), sizeof(valueInversed));
        }
    }
#pragma endregion

bool CSFparser::IsASCII(string strSample)
{
    return false;
}

string CSFparser::CharArrayToString(int arrayLength, char* pArray)
{
    stringstream ss;
    
    for(int i = 0 ; i < arrayLength; i++)
        ss << pArray[i];

    return ss.str();
}

wstring CSFparser::WharArrayToWstring(int arrayLength, wchar_t* pArray)
{
    wstringstream wss;
    
    for(int i = 0 ; i < arrayLength; i++)
        wss << pArray[i];

    return wss.str();
}
