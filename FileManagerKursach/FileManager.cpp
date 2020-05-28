
#include <windows.h>
#include <io.h>
#include <iostream>
#include <ctime>
#include <cstdio>
#include <direct.h>
#include <fstream>
#include "FileManager.h"


void FileManager::GetFolders()
{
	strcpy(pathfind, CurrentPath);
	strcat(pathfind, "\\*.*");

	int result = _findfirst(pathfind, &fileinfo);

	int flag = result;

	while (flag != -1){
		if (strcmp(fileinfo.name, ".") && strcmp(fileinfo.name, "..")){

			if (fileinfo.attrib&_A_SUBDIR) {
				filelist.push_back(File(fileinfo,CurrentPath));

			}
		}

		flag = _findnext(result, &fileinfo);
	}

	_findclose(result);
}

bool FileManager::SetHiddenAttr(const char* path)
{
    DWORD attr = GetFileAttributesA(path);
    if ((attr & FILE_ATTRIBUTE_HIDDEN) == 0)
    {
        if(SetFileAttributesA(path, attr | FILE_ATTRIBUTE_HIDDEN)==0)
            return false;
        else return true;
    }
    return false;
}

bool FileManager::SetRdonlyAttr(const char* path)
{
    DWORD attr = GetFileAttributesA(path);
    if ((attr & FILE_ATTRIBUTE_READONLY) == 0)
    {
        if(SetFileAttributesA(path, attr | FILE_ATTRIBUTE_READONLY)==0)
            return false;
        else return true;
    }
    return false;
}

bool FileManager::ResetRdoAttr(const char* path)
{
    DWORD attr = GetFileAttributesA(path);
    if ((attr & FILE_ATTRIBUTE_READONLY) == FILE_ATTRIBUTE_READONLY)
    {
        if(SetFileAttributesA(path, attr & ~FILE_ATTRIBUTE_READONLY)==0)
            return false;
        else return true;
    }
    return false;
}

bool FileManager::ResetHidAttr(const char* path)
{
    DWORD attr = GetFileAttributesA(path);
    if ((attr & FILE_ATTRIBUTE_HIDDEN) == FILE_ATTRIBUTE_HIDDEN)
    {
    if(SetFileAttributesA(path, attr & ~FILE_ATTRIBUTE_HIDDEN)==0)
        return false;
    else return true;
    }
    return false;
}

void FileManager::GetDrives()
{
	char buff[512];
	GetLogicalDriveStringsA(500, buff);
	for (int i=0,k = 0; i <= 100;k++)
	{
		if (buff[i] == '\0')
			break;
		drives.push_back(string());
		drives[k] = buff[i];
		i += 4;
	}
}

int FileManager::CommandChangeDrive(string drive)
{
    ChangeDrive(drive);
    strcpy(pathfind, CurrentPath);
    strcat(pathfind, "\\*.*");
    int result = _findfirst(pathfind, &fileinfo);
    if(result==-1)
        return 1;
    else
    {
        GetFileFolders();
        return 0;
    }

}
void FileManager::ChangeDrive(string drive)
{
	char temp[10];
	strcpy(temp, drive.c_str());
	strcpy(CurrentPath, temp);
	strcat(CurrentPath, ":\\");
}

void FileManager::OpenFile(File file)
{

    ShellExecuteA(NULL, NULL, file.GetPath(), NULL, NULL, SW_RESTORE);
}

vector<File> FileManager::GetListOfFiles()
{
	vector<File> tmp;
	if (showHidden == true)
	{
		tmp = filelist;
		return tmp;
	}
	else 
	{
        for (auto it = filelist.begin();it!=filelist.end();it++)
		{
            if (it->IsHidden() == false)
                tmp.push_back(*it);
		}
		return tmp;
	}

}

void FileManager::GetFile()
{
		_finddata_t fileinfo;

		char pathfind[MAX_PATH];
		strcpy(pathfind, CurrentPath);
		strcat(pathfind, "\\*.*");


		int result = _findfirst(pathfind, &fileinfo);

		int flag = result;

		while (flag != -1){
			if (strcmp(fileinfo.name, ".") && strcmp(fileinfo.name, "..")){

				
				if (!(fileinfo.attrib&_A_SUBDIR)) {
					filelist.push_back(File(fileinfo,CurrentPath));

				}
			}

		flag = _findnext(result, &fileinfo);
		}

	_findclose(result);
}

void FileManager::setPath(const char* curDir){
	strcpy_s(CurrentPath, curDir);


}

void FileManager::SetHidON()
{
	this->showHidden = true;
}

void FileManager::SetHidOFF()
{
	this->showHidden = false;
}



const char* FileManager::getPath()
{
	return CurrentPath;
}

vector<string> FileManager::ShowDrive()
{
	return drives;
}

int FileManager::CommandCD(const char* path)
{
	strcpy(ToPath, path);

	if (ToPath[1] == ':') {
		strcpy(CurrentPath, ToPath);
		if (ToPath[strlen(ToPath) - 1] != '\\'){
			strcat(CurrentPath, "\\");
		}
        strcpy(pathfind, CurrentPath);
        strcat(pathfind, "\\*.*");
        int result = _findfirst(pathfind, &fileinfo);
        if (result == -1) return 1;
		GetFileFolders();
        return 0;
	}
    return 1;
}

int FileManager::CommandChangeHidAttr(File file)
{
    if(SetHiddenAttr(file.GetPath()))
        return 0;
    else return 1;
}

int FileManager::CommandChangeRdoAttr(File file)
{
    if(SetRdonlyAttr(file.GetPath()))
        return 0;
    else return 1;
}

int FileManager::CommandResetHidAttr(File file)
{
    if(ResetHidAttr(file.GetPath()))
        return 0;
    else return 1;
}

int FileManager::CommandResetRdoAttr(File file)
{
    if(ResetRdoAttr(file.GetPath()))
        return 0;
    else return 1;
}


int FileManager::CommandCOPY(File file, const char* ToPath)
{								
	
	if (ValidationFilePath(file.GetPath()))
	{
		if (Copy_File(file.GetPath(), ToPath))
			return 0;
		else
			return 1;
	}
	else
	{
		CopyFileFolders(file.GetPath(), ToPath);
		if (GetLastError() == 5)
			return 1;
		else return 0;
	}

}

void FileManager::CopyFileFolders(const char* From, const char* To){

	_finddata_t fileinfo;

	char FromPach[MAX_PATH];
	strcpy(FromPach, From);
	int sizeFrom = strlen(FromPach);


	char ToPach[MAX_PATH];
	strcpy(ToPach, To);

	int index = sizeFrom - 3;
	while (From[index] != '\\')
		index--;

	strcat(ToPach, &From[index]);
	int sizeTo = strlen(ToPach);

	CreateDir(ToPach);

	char pathfind[MAX_PATH];
	strcpy(pathfind, From);
	strcat(pathfind, "\\*.*");


	int result = _findfirst(pathfind, &fileinfo);

	int flag = result;
	while (flag != -1){
		if (strcmp(fileinfo.name, ".") && strcmp(fileinfo.name, "..")){


			if (fileinfo.attrib&_A_SUBDIR) {
				strcat(FromPach, "\\");
				CopyFileFolders(strcat(FromPach, fileinfo.name), ToPach);
				FromPach[sizeFrom] = '\0';
				ToPach[sizeTo] = '\0';
			}
			else{
				strcat(FromPach, "\\");
				strcat(ToPach, "\\");
				Copy_File(strcat(FromPach, fileinfo.name), ToPach);
				FromPach[sizeFrom] = '\0';
				ToPach[sizeTo] = '\0';
			}
		}

		flag = _findnext(result, &fileinfo);
	}

	_findclose(result);
}

bool FileManager::Copy_File(const char* FromCopy, const char* WhereToCopy){
	bool flag = false;
	const int size = 4096;
	char buffer[size] = {};

	strcpy(ToPath, WhereToCopy);
	strcat(ToPath, "\\");
	strcat(ToPath, (strrchr(FromCopy, '\\') + 1));

	std::ifstream in(FromCopy, std::ios::binary | std::ios::in);
	if (in){

		std::ofstream out(ToPath, std::ios::binary | std::ios::out);
		if (out)
			flag = true;
		while (!in.eof()){
			in.read(buffer, size);
			out.write(buffer, in.gcount());
		}
		out.close();
	}
	in.close();
	return flag;
}

int FileManager::CommandMOVE(File file, const char* toPath)
{
	if (MoveFileFolders(file.GetPath(), toPath))
		return 0;
	else return 1;
}

void FileManager::CommandCDParent()
{
	if (strlen(CurrentPath) == 3)
		return;
	*strrchr(CurrentPath, '\\') = '\0';
	*(strrchr(CurrentPath, '\\') + 1) = '\0';
	GetFileFolders();
}

void FileManager::CommandCDRoot()
{
	CurrentPath[3] = '\0';
	GetFileFolders();
}

bool FileManager::MoveFileFolders(const char* from, const char* WhereToMove)
{				
	strcpy(ToPath, WhereToMove);
	strcat(ToPath, "\\");
	strcat(ToPath, (strrchr(from, '\\') + 1));

	if (MoveFileExA(from, ToPath, MOVEFILE_COPY_ALLOWED | MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) == 0)
	{
		return false;
	}
	else
		return true;
}

int FileManager::CommandFILE(const char* name)
{
    strcpy(pathfind,CurrentPath);
    strcat(pathfind,"\\");
    strcat(pathfind,name);
    if (FileCreation(pathfind))
		return 0;
	else return 1;
}

bool FileManager::FileCreation(const char* path)
{	
	std::ofstream out(path);
	if (out)
    {
        out.close();
		return true;
    }
	else
		return false;

}

int FileManager::CommandRENAME(File file, const char* newName) {
	if (file.IsRdonly()) return 1;
	if (RenamFileOrFolder(file.GetPath(), newName))
		return 0;
	else return 1;
}

bool FileManager::RenamFileOrFolder(const char* path, const char* newName){

	bool flag = false;
	strcpy(ToPath, path);
	*(strrchr(ToPath, '\\') + 1) = '\0';
	strcat(ToPath, newName);


	if (rename(path, ToPath))
		flag = false;
	else
		flag=true;
	return flag;
}

int FileManager::CommandMKDIR(const char* name) {
    strcpy(pathfind,CurrentPath);
    strcat(pathfind,"\\");
    strcat(pathfind,name);
    if (CreateDir(pathfind))
		return 0;
	else
		return 1;
}

bool FileManager::CreateDir(const char* path){

	if (_mkdir(path) == -1)
		return false;
	else
		return true;
}

int FileManager::CommandDEL(File file) 
{							
	if (ValidationFilePath(file.GetPath()))
	{
		if (DeletFileOrFolder(file.GetPath()))
			return 0;
		else
			return 1;
	}
	else 
	{

		DeleteNonEmptyDirectory(file.GetPath());
		if (DeletFileOrFolder(file.GetPath()))
			return 0;
		else
			return 1;
	}
}

void FileManager::DeleteNonEmptyDirectory(const char* path) 
{				

	_finddata_t fileinfo;

	char FromPach[MAX_PATH];
	strcpy(FromPach, path);
	int sizeFrom = strlen(FromPach);

	char pathfind[MAX_PATH];
	strcpy(pathfind, FromPach);
	strcat(pathfind, "\\*.*");


	int result = _findfirst(pathfind, &fileinfo);

	int flag = result;
	while (flag != -1){
		if (strcmp(fileinfo.name, ".") && strcmp(fileinfo.name, "..")){


            if (fileinfo.attrib&_A_SUBDIR) {
				strcat(FromPach, "\\");
				if (EmptyDirectory(strcat(FromPach, fileinfo.name))){
					DeleteNonEmptyDirectory(FromPach);
                    DeletFileOrFolder(FromPach);
					*(strrchr(FromPach, '\\') + 1) = '\0';
				}
				else {
					DeletFileOrFolder(FromPach);
					*(strrchr(FromPach, '\\') + 1) = '\0';
				}
			}
			else{
				strcat(FromPach, "\\");
				DeletFileOrFolder(strcat(FromPach, fileinfo.name));
				*(strrchr(FromPach, '\\') + 1) = '\0';
			}
		}

		flag = _findnext(result, &fileinfo);
	}

	_findclose(result);
}

bool FileManager::DeletFileOrFolder(const char* path){
    bool flag = true;
	if (remove(path) != 0)
		if (_rmdir(path) == -1)
            flag = false;

	return flag;
}


void FileManager::GetFileFolders(){
    filelist.clear();
	GetFolders();
	GetFile();
}

FileManager::FileManager()
{
	GetDrives();
}

bool FileManager::ValidationFilePath(const char* path){
	bool flag = true;

	std::ifstream in(path, std::ios::binary | std::ios::in);
	if (!in)
		flag = false;

	return flag;
}

bool FileManager::EmptyDirectory(const char* path) {
	strcpy(pathfind, path);
	strcat(pathfind, "\\*.*");

	// Начало Поиска
	int result = _findfirst(pathfind, &fileinfo);
	bool IsEmpty = false;
	int flag = result;

	while (flag != -1){
		if (strcmp(fileinfo.name, ".") && strcmp(fileinfo.name, ".."))	IsEmpty = true;

		flag = _findnext(result, &fileinfo);
	}

	_findclose(result);

	return IsEmpty;
}
