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
        ifstream fileToParse{Path, ios::binary | ios::in};

        if(fileToParse.is_open())
        {
            fileToParse.read(reinterpret_cast<char*>(&Header), sizeof(CSFHeader));

            for(;;)
            {
                
            }
        }

        fileToParse.close();
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
