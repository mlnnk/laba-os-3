#include "marker_logic.h"
#include <cstdlib>
#include<windows.h>
MarkerLogic::MarkerLogic(int id, int arraySize)
    : id(id), arraySize(arraySize), markedCount(0)
{
    srand(id);
}

bool MarkerLogic::step(std::vector<int>& arr, int& blockedIndex) {
    if (arraySize == 0) return false;
    int index = rand() % arraySize;

    if (arr[index] == 0) {
        Sleep(5);
        arr[index] = id;
        Sleep(5);
        markedCount++;
        return true;
    }
    else {
        blockedIndex = index;
        return false;
    }
}
