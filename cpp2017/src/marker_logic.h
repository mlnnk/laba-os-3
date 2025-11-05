#pragma once
#include <vector>

class MarkerLogic {
public:
    MarkerLogic(int id, int arraySize);
    bool step(std::vector<int>& arr, int& blockedIndex);
    int getMarkedCount() const { return markedCount; }

private:
    int id;
    int arraySize;
    int markedCount;
};
