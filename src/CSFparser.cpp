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

        cout << "First 4th bytes are : [" << Header.csfChars[0] 
                                          << Header.csfChars[1] 
                                          << Header.csfChars[2] 
                                          << Header.csfChars[3] << "]" << endl;
        cout << "formatVersion       : [" << Header.formatVersion << "]" << endl;
        cout << "numberOfLabels      : [" << Header.numberOfLabels << "]" << endl;
        cout << "numberOfStrings     : [" << Header.numberOfStrings << "]" << endl;
        cout << "uselessBytes        : [" << Header.uselessBytes << "]" << endl;
        cout << "languageCode        : [" << Header.languageCode << "]" << endl << endl;
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
            for (int tmp = 0; tmp < 4; tmp++)
            {
                if (lbl[tmp] != LBL[tmp])
                {
                    if (i > 0) i--;
                    breakFlag = true;
                    break;;
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

            cout << "countOfStrings  : [" << countOfStrings << ']' << endl;
            cout << "labelNameLength : [" << labelNameLength << ']' << endl;
            cout << "Name            : [" ;
            for (uint8_t tmp: labelName) cout << (char)tmp;
            cout << "]" << endl;

            string stringValue = "";
            string extraStringValue = "";

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

                cout << "String : [" ;
                for (const wchar_t tmp: _stringValue) cout << tmp;
                cout << "]" << endl;

                // Reverse read string
                uint8_t tmpArray[valueLenght * 2];
                
                cout << "STOP, HAMMER TIME" << endl;
                cin >> breakFlag;

                for (wchar_t &tmp: _stringValue)
                    tmp = ~tmp;

                cout << "STOP, HAMMER TIME" << endl;
                cin >> breakFlag;
                
                cout << endl;

                break; // DELETE THIS
            }
            /*
             UInt32 labelNameLength = br.ReadUInt32();                    // длина названия лейбла
                char[] labelName = br.ReadChars((int)labelNameLength); // само название лейбла

                byte[] stringValue = FileEncoding.GetBytes(string.Empty);
                char[] extraStringValue = string.Empty.ToCharArray();

                if (countOfStrings != 0) // отбрасывание строк с пустыми значениями, а то падения проги не избежать
                {
                    // чтение значения лейбла
                    char[] rtsOrWrts = br.ReadChars(4);                                // ' RTS' - доп. значения нет. 'WRTS' - доп. значение есть.
                    UInt32 valueLength = br.ReadUInt32();                                // длина строки юникода, укороченная вдвое
                    stringValue = br.ReadBytes(Convert.ToInt32(valueLength * 2)); // строка, конвертированная в интертированные байты

                    InvertAllBytesInArray(stringValue);

                    // чтение дополнительного значения лейбла
                    if (new string(rtsOrWrts) == new string(WRTS))
                    {
                        UInt32 extraValueLength = br.ReadUInt32();                                 // длина доп. значения
                        extraStringValue = br.ReadChars(Convert.ToInt32(extraValueLength)); // само доп значение (проблема поддержки кодировки отличной от Unicode)
                    }
                }

                if (extraStringValue == string.Empty.ToCharArray())
                    Table.Add(new StringTableString(new string(labelName), new string(FileEncoding.GetChars(stringValue))));
                else
                    ExtraTable.Add(new StringTableExtraString(new string(labelName), new string(FileEncoding.GetChars(stringValue)), new string(extraStringValue)));
            }
            */
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
