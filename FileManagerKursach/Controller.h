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


    vector<string>leftdrives;
    vector<string>rightdrives;

    File leftchosenfile, rightchosenfile;
    vector<File> leftshowlist, rightshowlist;
    FileManager LeftManager, RightManager;

    stack<string>rightUndoAdress;
    stack<string>rightRedoAdress;

    stack<string>UndoAdress;
    stack<string>RedoAdress;

    void leftRedo();
    void leftUndo();

    void rightRedo();
    void rightUndo();

    void changeleftAdress();

    void changerightAdress();

};
