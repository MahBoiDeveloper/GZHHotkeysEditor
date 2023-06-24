#include "CSFparser.hpp"

#pragma region Initialization and finilization
    CSFparser::CSFparser()
{
    pTable = new list<CompiledString>();
    pExtraTable = new list<ExtraCompiledString>();
}

    CSFparser::CSFparser(const string& filePath) : Path(filePath)
    {
        pTable = new list<CompiledString>();
        pExtraTable = new list<ExtraCompiledString>();
        Parse();
    }

    CSFparser::~CSFparser()
    {
        wcout << "Normal strings count [" << pTable->size() << "] | Extra strings count [" << pExtraTable->size() << ']' << endl;
        delete pTable;
        delete pExtraTable;
    }
#pragma endregion

#pragma region Parsing
    void CSFparser::Parse()
    {
        ifstream csfFile{Path, ios::binary | ios::in};

        if (csfFile.is_open())
        {
            CSFparser::ParseHeader(&csfFile);
            CSFparser::ParseBody(&csfFile);
        }

        csfFile.close();
    }

    inline void CSFparser::ParseHeader(ifstream* csfFile)
    {
        csfFile->read(reinterpret_cast<char*>(&Header), sizeof(Header));

        #if DEBUG
        wcout << "First 4th bytes are : [" << (wchar_t)Header.csfChars[0] 
                                          << (wchar_t)Header.csfChars[1] 
                                          << (wchar_t)Header.csfChars[2] 
                                          << (wchar_t)Header.csfChars[3] << "]" << endl;
        wcout << "formatVersion       : [" << Header.formatVersion << "]" << endl;
        wcout << "numberOfLabels      : [" << Header.numberOfLabels << "]" << endl;
        wcout << "numberOfStrings     : [" << Header.numberOfStrings << "]" << endl;
        wcout << "uselessBytes        : [" << Header.uselessBytes << "]" << endl;
        wcout << "languageCode        : [" << Header.languageCode << "]" << endl << endl;
        #endif
    }

    inline void CSFparser::ParseBody(ifstream* csfFile)
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
                uint8_t  rtsWrts[4];
                csfFile->read(reinterpret_cast<char*>(&rtsWrts), sizeof(rtsWrts));

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

                // Read extra value
                if((char)rtsWrts[0] == 'W')
                {
                    uint32_t extraValueLength;
                    csfFile->read(reinterpret_cast<char*>(&extraValueLength), sizeof(extraValueLength));

                    uint8_t extraValue[extraValueLength];
                    csfFile->read(reinterpret_cast<char*>(&extraValue), sizeof(extraValue));

                    extraStringValue = CSFparser::CharArrayToString(sizeof(extraValue), reinterpret_cast<char*>(extraValue));

                    pExtraTable->push_back({stringName, stringValue, extraStringValue});
                }
                {
                    pTable->push_back({stringName, stringValue});
                }
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

    }

    void CSFparser::Save(string strFileName)
    {

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
