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
    int CommandMKDIR(const char*);
	int CommandRENAME(File file, const char*);
    int CommandFILE(const char*);
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
			
    bool DeletFileOrFolder(const char*);
    void DeleteNonEmptyDirectory(const char*);

    bool CreateDir(const char*);

    bool RenamFileOrFolder(const char*, const char*);

    bool FileCreation(const char*);

    void CopyFileFolders(const char*, const char*);
    bool Copy_File(const char*, const char*);
				
    bool MoveFileFolders(const char*, const char*);
    bool ValidationFilePath(const char*);
	
    bool EmptyDirectory(const char*);
};


