#include "marker_logic.h"
#include <cstdlib>

MarkerLogic::MarkerLogic(int id, int arraySize)
    : id(id), arraySize(arraySize), markedCount(0)
{
    srand(id); 
}

bool MarkerLogic::step(std::vector<int>& arr) {
    if (arraySize == 0) return false;
    int index = rand() % arraySize;

    if (arr[index] == 0) {
        arr[index] = id;
        markedCount++;
        return true;
    }
    else {
        return false;
    }
}
