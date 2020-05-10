#pragma once
#include <windows.h>
#include <iostream>
#include <conio.h>
#include "File.h"
#include "FileManager.h"
#include <stack>

class Controller
{
public:
    Controller(){}

    stack<string>rightUndoAdress;
    stack<string>rightRedoAdress;

    stack<string>UndoAdress;
    stack<string>RedoAdress;

    void leftRedo();
    void leftUndo();

    void changeleftAdress();

    vector<string>leftdrives;
    vector<string>rightdrives;

    File leftchosenfile, rightchosenfile;
    vector<File> leftshowlist, rightshowlist;
    FileManager LeftManager, RightManager;
};
