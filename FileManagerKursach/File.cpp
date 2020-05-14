


#include "File.h"
#include <windows.h>
#include <io.h>
#include <iostream>
#include <ctime>
#include <cstdio>
#include <direct.h>
#include <fstream>

string File::GetName()
{
	string tmp( this->fileinfo.name);
	return tmp;
}

int File::GetSize()
{
    if(this->IsSubdir())
    {
        int count=0;
        _finddata_t fileinfo;

        char pathfind[MAX_PATH];
        strcpy(pathfind, this->path);
        strcat(pathfind, "\\*.*");
        int result = _findfirst(pathfind, &fileinfo);
        int flag = result;
        while (flag != -1)
        {
            if (strcmp(fileinfo.name, ".") && strcmp(fileinfo.name, ".."))
            {
                count++;
            }
                flag = _findnext(result, &fileinfo);
        }
    _findclose(result);
    return count;
    }

	return this->fileinfo.size;
}

tm* File::GetTimeCreate()
{
	tm* timeinfo;
    timeinfo = _localtime64(&this->fileinfo.time_create);
	return timeinfo;
}

tm* File::GetTimeWrite()
{
    tm* timeinfo;
    timeinfo = _localtime64(&this->fileinfo.time_write);
    return timeinfo;
}

bool File::IsHidden()
{
	return this->fileinfo.attrib & _A_HIDDEN;
}

bool File::IsArch()
{
	return this->fileinfo.attrib & _A_ARCH;
}

bool File::IsSys()
{
	return this->fileinfo.attrib & _A_SYSTEM;
}

bool File::IsSubdir()
{
	return this->fileinfo.attrib & _A_SUBDIR;
}

bool File::IsRdonly()
{
	return this->fileinfo.attrib & _A_RDONLY;
}

void File::SetInfo(_finddata_t info)
{
	this->fileinfo = info;
}

void File::SetPath(const char* path)
{
	strcpy_s(this->path, path);
}

const char* File::GetPath()
{
	return this->path;
}

DWORD File::GetAttr()
{
    return this->fileinfo.attrib;
}

string File::GetExp()
{
    if(this->IsSubdir())
    {
        string tmps="";
        return tmps;
    }
    char tmp[MAX_PATH];
    if( strrchr(fileinfo.name,'.')==NULL)
    {
        string tmps="";
        return tmps;
    }
    strcpy(tmp,strrchr(fileinfo.name,'.')+1);

    string tmps = string(tmp);
    return tmps;
}
