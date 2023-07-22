#include <exception>
#include <fstream>

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

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
            JsonMainObject = QJsonDocument::fromJson(QByteArray::fromStdString(tmpString)).object();
            openedFile.close();
        }
        else
        {
            throw ExceptionMessage(string("Bad file name; unable to open file \"" + FileName + "\""));
        }
    }
#pragma endregion

#pragma region Getters
    string JSONFile::GetValue(const string& strThisLayoutParameter) const
    {
        return JsonMainObject.value(QString::fromStdString(strThisLayoutParameter)).toString().toStdString();
    }

    QJsonValue JSONFile::GetObject(const std::string& strThisLayoutParameter) const
    {
        return JsonMainObject.value(QString::fromStdString(strThisLayoutParameter));
    }
#pragma endregion
