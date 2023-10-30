#include <exception>
#include <fstream>

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

#include "JSONFile.hpp"
#include "Exception.hpp"

using namespace std;

#pragma region CTORs and DTORs
    JSONFile::JSONFile(const string& filePath) : FileName{filePath}
    {
        QFile openedFile(FileName.c_str());

        // Reading json file
        if (openedFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            string tmpString = openedFile.readAll().toStdString();
            JsonMainObject   = QJsonDocument::fromJson(QByteArray::fromStdString(tmpString)).object();
            openedFile.close();
        }
        else
        {
            throw Exception(string("Bad file name; unable to open file \"" + FileName + "\""));
        }
    }
#pragma endregion

#pragma region Getters
    string JSONFile::GetValue(const string& strThisLayoutParameter) const
    {
        return JsonMainObject.value(QString::fromStdString(strThisLayoutParameter)).toString().toStdString();
    }

    QJsonValue JSONFile::GetObject(const string& strThisLayoutParameter) const
    {
        return JsonMainObject.value(QString::fromStdString(strThisLayoutParameter));
    }

    QJsonObject JSONFile::Query(const string& strQuery) const
    {
        QString qstrQuery = QString::fromStdString(strQuery);
        return JsonMainObject.value(qstrQuery).toObject();
    }

    bool JSONFile::EvaluateQuery(const string& strQuerySample) const
    {
        return false;
    }
#pragma endregion
