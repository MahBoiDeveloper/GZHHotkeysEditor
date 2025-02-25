#pragma once
#include <string>
#include <concepts>
#include <QString>

template<class T>
concept IsSymbol = std::same_as<T, char> || std::same_as<T, wchar_t> || std::same_as<T, QChar>;

template<class T>
concept IsCString = std::same_as<T, const char*> || std::same_as<T, const wchar_t*>;

template<class T>
concept IsSTDString = std::same_as<T, std::string> || std::same_as<T, std::wstring>;

template<class T>
concept IsNumber = std::same_as<T, int> || std::same_as<T, size_t> || std::same_as<T, std::size_t> || std::same_as<T, ushort>;

template<IsNumber N> inline QString operator+ (const QString& str,          const N& num)                { return QString(str).append(QString::number(num)); }
template<IsNumber N> inline QString operator+ (const N& num,                const QString& str)          { return QString::number(num).append(str); }
template<IsNumber N> inline QString operator+ (const N& num,                const std::string& str)      { return QString::number(num).append(QString::fromStdString(str)); }
template<IsNumber N> inline QString operator+ (const std::string& str,      const N& num)                { return QString::fromStdString(str).append(QString::number(num)); }
template<IsSymbol C> inline QString operator+ (const C& char1,              const C& char2)              { return QString(char1).append(char2); }
template<IsSymbol C> inline QString operator+ (const QString& str,          const C& ch)                 { return QString(str).append(ch); }
template<IsSymbol C> inline QString operator+ (const C& ch,                 const QString& str)          { return QString(ch).append(str); }
                     inline QString operator+ (const QString& qstr,         const wchar_t* wstr)         { return QString(qstr).append(QString::fromStdWString(std::wstring(wstr))); }
                     inline QString operator+ (const QString& qstr,         const std::wstring& stdwstr) { return QString(qstr).append(QString::fromStdWString(stdwstr)); }
                     inline QString operator+ (const std::wstring& stdwstr, const QString& qstr)         { return QString::fromStdWString(stdwstr).append(qstr); }
                     inline QString operator+ (const QString& qstr,         const std::string& stdstr)   { return QString(qstr).append(QString::fromStdString(stdstr)); }
                     inline QString operator+ (const std::string& stdstr,   const QString& qstr)         { return QString::fromStdString(stdstr).append(qstr); }
