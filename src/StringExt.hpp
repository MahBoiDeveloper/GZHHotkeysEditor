#pragma once
#include <string>
#include <concepts>
#include <QString>

#define L10N(x)   StringExt::l10n(x)
#define nameof(x) QString(#x)

inline QString ToQString(const std::string& str)  { return QString::fromStdString(str); }
inline QString ToQString(const std::wstring& str) { return QString::fromStdWString(str); }
inline QString ToQString(const QString& str)      { return str; }
inline QString ToQString(const char* ch)          { return ToQString(std::string(ch)); }
inline QString ToQString(const wchar_t* ch)       { return ToQString(std::wstring(ch)); }
inline QString ToQString(const char ch)           { return QString(QChar(ch)); }
inline QString ToQString(const wchar_t ch)        { return QString(QChar(ch)); }

namespace StringExt
{
    const QString EmptyString("");
    QString l10n(const char*         string);
    QString l10n(const QString&      string);
    QString l10n(const std::string&  string);
    QString l10n(const std::wstring& string);
}

template<class T>
concept IsNumber = std::same_as<T, int> || std::same_as<T, size_t> || std::same_as<T, std::size_t> || std::same_as<T, ushort>;

template<class T>
concept IsSymbol = std::same_as<T, char> || std::same_as<T, wchar_t> || std::same_as<T, QChar>;

template<class T>
concept IsCString = std::same_as<T, const char*> || std::same_as<T, const wchar_t*>;

template<class T>
concept IsSTDString = std::same_as<T, std::string> || std::same_as<T, std::wstring>;

template<class T>
concept IsString = std::same_as<T, const char*> || std::same_as<T, const wchar_t*> || 
                   std::same_as<T, std::string> || std::same_as<T, std::wstring> || 
                   std::same_as<T, QString>;

template<IsString S, IsString T> inline QString operator+ (const S& str1, const T& str2)          { return ToQString(str1).append(ToQString(str2)); }
template<IsString S, IsNumber N> inline QString operator+ (const S& str,  const N& num)           { return ToQString(str).append(QString::number(num)); }
template<IsNumber N, IsString S> inline QString operator+ (const N& num,  const S& str)           { return QString::number(num).append(ToQString(str)); }
template<IsString S, IsSymbol C> inline QString operator+ (const S& str,  const C& ch)            { return ToQString(str).append(ToQString(ch)); }
template<IsSymbol C, IsString S> inline QString operator+ (const S& str,  const C& ch)            { return ToQString(str).append(ToQString(ch)); }
                                 inline QString operator+ (const QString& qstr, const bool& flag) { return QString(qstr).append(flag ? "true" : "false"); }
