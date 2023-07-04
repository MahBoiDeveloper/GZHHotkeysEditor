#include "Helper.hpp"

Helper::Helper()
{
}

Helper::~Helper()
{
}

string Helper::GetUUID()
{
	stringstream ss;

	// Magic code by stackoverflow: https://stackoverflow.com/questions/24365331/how-can-i-generate-uuid-in-c-without-using-boost-library
	UUID uuid;
	auto tmpUuidCreate = UuidCreate(&uuid);
	char* str;
	auto tmpUuidToStringA = UuidToStringA(&uuid, (RPC_CSTR*)(&str));
	ss << str << endl;
	RpcStringFreeA((RPC_CSTR*)(&str));

	return ss.str();
}

string Helper::GetCurrentTime()
{
    time_t timeStomp = time(nullptr);
    tm timeNow;
    localtime_s(&timeNow, &timeStomp);

    char currentTime[128];
    strftime(currentTime, sizeof(currentTime), "%Y-%m-%d %X", &timeNow);

    stringstream ss;
    ss << currentTime;

    return ss.str();
}


bool Helper::IsASCII(string strSample)
{
    return false;
}

string Helper::CharArrayToString(int arrayLength, char* pArray)
{
    stringstream ss;
    
    for(int i = 0 ; i < arrayLength; i++)
        ss << pArray[i];

    return ss.str();
}

wstring Helper::WharArrayToWstring(int arrayLength, wchar_t* pArray)
{
    wstringstream wss;
    
    for(int i = 0 ; i < arrayLength; i++)
        wss << pArray[i];

    return wss.str();
}
