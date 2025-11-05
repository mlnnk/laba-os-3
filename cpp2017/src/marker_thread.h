#pragma once
#include <windows.h>
#include <vector>
#include "marker_logic.h"

struct MarkerParams {
    int id;
    std::vector<int>* array;
    HANDLE startEvent;
    HANDLE stopEvent;
    HANDLE resumeEvent;
    HANDLE doneEvent;
    CRITICAL_SECTION* printCS; 
};

DWORD WINAPI MarkerThread(LPVOID param);
