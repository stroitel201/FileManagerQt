#pragma once
#include <windows.h>
#include <iostream>
#include <conio.h>
#include "File.h"
#include "FileManager.h"


class Controller
{
public:
    Controller(){}


    vector<string>leftdrives;
    vector<string>rightdrives;

    File leftchosenfile, rightchosenfile;
    vector<File> leftshowlist, rightshowlist;
    FileManager LeftManager, RightManager;
};
