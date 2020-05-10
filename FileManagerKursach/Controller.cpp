#pragma once
#include "Controller.h"


void Controller::changeleftAdress()
{
    UndoAdress.push(string(LeftManager.getPath()));
}

void Controller::leftRedo()
{
    char path[MAX_PATH];
    UndoAdress.push(RedoAdress.top());

    string temp = RedoAdress.top();
    strcpy_s(path,temp.c_str());
    LeftManager.setPath(path);
    RedoAdress.pop();
}

void Controller::leftUndo()
{
    char path[MAX_PATH];
    RedoAdress.push(UndoAdress.top());
    UndoAdress.pop();
    string temp = UndoAdress.top();
    strcpy_s(path,temp.c_str());
    LeftManager.setPath(path);

}
