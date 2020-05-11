
#pragma once

#include<iostream>
#include<vector>
#include <io.h>
#include <string>
#include <windows.h>
using namespace std;

class File
{
public:
    File(){}
	File(_finddata_t info, const char* curpath)
	{
		this->fileinfo = info;
		strcpy(this->path, curpath);
        strcat(this->path, "\\");
		strcat(this->path, fileinfo.name);
	}
    File(const File& file)
    {
        strcpy(this->path,file.path);
        this->fileinfo=file.fileinfo;
    }
    File& operator =(const File& file)
    {
        strcpy(this->path,file.path);
        this->fileinfo=file.fileinfo;
        return *this;
    }
	string GetName();
	int GetSize();
    tm* GetTimeCreate();
    tm* GetTimeWrite();
	bool IsHidden();
	bool IsArch();
	bool IsSys();
	bool IsSubdir();
	bool IsRdonly();
    DWORD GetAttr();
	void SetInfo(_finddata_t info);
	void SetPath(const char* path);
	const char* GetPath();
    string GetExp();
private:
	_finddata_t fileinfo;
	char path[260];
};
