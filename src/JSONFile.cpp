#include <exception>

#include <QFile>
#include <QJsonDocument>

#include "JSONFile.hpp"
#include "ExceptionMessage.hpp"

using namespace std;

#pragma region ctor and dtor
    JSONFile::JSONFile(const string& filePath) : FileName{filePath}
    {
        QFile openedFile(FileName.c_str());
        
        if (openedFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            string tmpString = openedFile.readAll().toStdString();

            ParsedData = QJsonDocument::fromJson(QByteArray::fromStdString(tmpString)).object();

            openedFile.close();
        }
        else
        {
            throw ExceptionMessage(string("Bad file name; unable to open file \"" + FileName + "\""));
        }
    }
#pragma endregion

#pragma region Getters
    std::string JSONFile::GetKeyValue(const std::string& keyName) const
    {
        return ParsedData.value(keyName.c_str()).toString().toStdString();
    }

    QJsonObject JSONFile::GetObject(const std::string& keyName) const
    {
        return ParsedData.value(keyName.c_str()).toObject();
    }
#pragma endregion
