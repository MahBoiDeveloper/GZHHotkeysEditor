#include <regex>
#include <QString>

#include "GINIParser.hpp"
#include "Exception.hpp"
#include "Logger.hpp"

using namespace std;

enum class LineStatus
{
    EmptyOrWrong = 0,
    SectionName,
    SectionKey,
    SectionFooter
};

#pragma region Parsing
    void GINIParser::Parse()
    {
        ifstream file(Path, ios::in)

        Logger::Instance->Log() << "Attempt to read file \"" << Path << "\"..." << endl;

        if (csfFile.is_open())
        {
            string buff, buffName, buffKeyName, buffKeyValue;
            LineStatus st;
            list<GINIKey> lstKeysBuffer;

            while(file.good())
            {

                file >> buff;

                // Erase comments
                buff.erase(buff.find(';'), buff.end);
                buff.shrink_to_fit();
                
                switch (st)
                {
                case LineStatus::SectionName   :
                    if (regex_match(buff.c_str(), regex("[A-Za-z0-9].* [A-Za-z0-9].*")));

                    break;
                
                case LineStatus::SectionKey    :
                    // regex for name (?<=  ).*(?= =)
                    // regex for value (?<== ).*
                    break;

                case LineStatus::SectionFooter :
                    if (QString::fromStdString(buff).toUpper() == "END")
                    {
                        lstKeysBuffer.push_back({buffKeyName, buffKeyValue});
                        st = LineStatus::SectionName;
                    }
                    break;
                }

                /*

                if (QString::fromStdString(buff).toUpper() == "END")
                {

                }
                if (buff.find('=') < buff.size())
                {
                    // GetKeyName
                    // GetKeyValue
                }

                */
            }

            Logger::Instance->Log() << "File \"" << Path << "\" has been parsed" << endl;
        }
        else
        {
            throw Exception(string("Bad file name; unable to open file \"" + Path + "\""));
        }

        csfFile.close();
    }

    void GINIParser::Save()
    {
        ofstream file(Path, ios::out);

        Logger::Instance->Log() << "Attempt to write file \"" << Path << "\"..." << endl;

        if (file.is_open())
        {
            for (const auto& elem : Sections)
            {
                file << elem.Name << endl;

                for (const auto& key : elem.Keys)
                {
                    file << "  " << key.Name << " = " << key.Value << endl;
                }

                file << "End" << endl;
            }

            Logger::Instance->Log() << "File \"" << Path << "\" has been saved." << endl;
        }
        else
        {
            throw Exception(string("Unable write settings to file \"" + Path + "\"; make sure program have right to write into folder and into file."));
        }
    }

    void GINIParser::Save(string strFileSample)
    {
        string tmp = Path;
        Path = strFileSample;
        Save();
        Path = tmp;
    }
#pragma endregion

#pragma region Getters and setter
    list<string> GINIParser::GetSectionsName() const
    {
        list<string> tmp;

        for (const auto& elem : Sections)
            tmp.push_back(elem.Name);

        return tmp;
    }

    list<string> GINIParser::GetSectionKeys(const string& strSectionName) const
    {
        list<string> tmp;

        for (const auto& elem : Sections)
            if (elem.Name == strSectionName)
            {
                tmp = elem.Keys;
                break;
            }
        
        return tmp;
    }

    string GINIParser::GetSectionValue(const string& strSectionName, const string& strSectionKey) const
    {
        string tmp;

        for (const auto& elem : Sections)
            if (elem.Name == strSectionName)
            {
                for (const auto& key : elem.Keys)
                    if (key.Name == strSectionKey)
                    {
                        tmp = key.Value;
                        break;
                    }

                break;
            }

        return tmp;
    }

    void GINIParser::SetSectionValue(const string& strName, const string& strKey, const string& strValue)
    {
        for (const auto& elem : Sections)
            if (elem.Name == strName)
            {
                for (const auto& key : elem.Keys)
                    if (key.Name == strKey)
                    {
                        key.Value == strValue;
                        break;
                    }

                break;
            }
    }
#pragma endregion
