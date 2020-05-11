#pragma once
#include<iostream>
#include<vector>
#include <io.h>
#include "File.h"
#include <windows.h>
#include <shellapi.h>


class FileManager
{
public:
	void setPath(const char*);					
	void SetHidON();
	void SetHidOFF();							

	void OpenFile(File file);
	vector<File> GetListOfFiles();
	const char* getPath();
	vector<string> ShowDrive();
	void GetFileFolders();
	FileManager();
	int CommandDEL(File file);
	int CommandMKDIR();
	int CommandRENAME(File file, const char*);
	int CommandFILE();
	int CommandCOPY(File file, const char*);
	int CommandMOVE(File file, const char*);
	void CommandCDParent();
	void CommandCDRoot();
    int CommandCD(const char* );
    int CommandChangeHidAttr(File file);
    int CommandChangeRdoAttr(File file);
    int CommandResetHidAttr(File file);
    int CommandResetRdoAttr(File file);
    int CommandChangeDrive(string drive);

private:
	char CurrentPath[MAX_PATH];					
	char FromPath[MAX_PATH];					
	char ToPath[MAX_PATH];						
	_finddata_t fileinfo;
	char pathfind[MAX_PATH];
    bool showHidden = false;
	vector<string> drives;
	vector<File> filelist;	


    bool SetHiddenAttr(const char*);
    bool SetRdonlyAttr(const char*);
    bool ResetRdoAttr(const char* path);
    bool ResetHidAttr(const char* path);

	void GetDrives();
    void ChangeDrive(string drive);

	void GetFile();							
	void GetFolders();							
			
	bool DeletFileOrFolder(const char*);		//	удаление файла или папки
	void DeleteNonEmptyDirectory(const char*);	//	удаление непустая директории

	bool CreateDir(const char*);				//	создание папки

	bool RenamFileOrFolder(const char*, const char*);		//	переименование файла или папки

	bool FileCreation(const char*);				//	создание файла

	void CopyFileFolders(const char*, const char*);	//	копирование файла (папки) из одной папки в другую
	bool Copy_File(const char*, const char*);		//	копирование файла
				
	bool MoveFileFolders(const char*, const char*);				//	перемещение файла (папки) из одной папки в другую

	bool ValidationFilePath(const char*);			//	проверка пути к файлу
	
	bool EmptyDirectory(const char*);				//	пустая директории
};


