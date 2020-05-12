#pragma once
#include "Controller.h"


void Controller::changeleftAdress()
{
    UndoAdress.push(string(LeftManager.getPath()));
}

void Controller::changerightAdress()
{
    rightUndoAdress.push(string(RightManager.getPath()));
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


void Controller::rightRedo()
{
    char path[MAX_PATH];
    rightUndoAdress.push(rightRedoAdress.top());

    string temp = rightRedoAdress.top();
    strcpy_s(path,temp.c_str());
    RightManager.setPath(path);
    rightRedoAdress.pop();
}

void Controller::rightUndo()
{
    char path[MAX_PATH];
    rightRedoAdress.push(rightUndoAdress.top());
    rightUndoAdress.pop();
    string temp = rightUndoAdress.top();
    strcpy_s(path,temp.c_str());
    RightManager.setPath(path);

}
