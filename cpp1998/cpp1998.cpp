#include <windows.h>
#include <iostream>
#include <vector>
#include "marker_thread.h"

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int size, n;
    std::cout << "Введите размер массива: ";
    std::cin >> size;

    std::vector<int> arr(size, 0);

    std::cout << "Введите количество потоков marker: ";
    std::cin >> n;

    HANDLE* threads = new HANDLE[n];
    MarkerParams** params = new MarkerParams * [n];
    HANDLE* doneEvents = new HANDLE[n];

    HANDLE startEvent = CreateEvent(NULL, TRUE, FALSE, NULL);


    CRITICAL_SECTION printCS;
    InitializeCriticalSection(&printCS);

    for (int i = 0; i < n; ++i) {
        doneEvents[i] = CreateEvent(NULL, TRUE, FALSE, NULL);

        params[i] = new MarkerParams;
        params[i]->id = i + 1;
        params[i]->array = &arr;
        params[i]->startEvent = startEvent;
        params[i]->stopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        params[i]->resumeEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
        params[i]->doneEvent = doneEvents[i];
        params[i]->printCS = &printCS;

        threads[i] = CreateThread(NULL, 0, MarkerThread, params[i], 0, NULL);
    }

    SetEvent(startEvent);

    int activeThreads = n;

    while (activeThreads > 0) {

        WaitForMultipleObjects(n, doneEvents, TRUE, INFINITE);

        EnterCriticalSection(&printCS);
        std::cout << "Состояние массива: ";
        for (int i = 0; i < arr.size(); ++i)
            std::cout << arr[i] << " ";
        std::cout << std::endl;
        LeaveCriticalSection(&printCS);

        int killId;
        std::cout << "Введите номер маркера для завершения: ";
        std::cin >> killId;

        int killIdx = killId - 1;
        if (killIdx < 0 || killIdx >= n || threads[killIdx] == NULL) {
            std::cout << "Некорректный номер" << std::endl;
            continue;
        }

        SetEvent(params[killIdx]->stopEvent);
        WaitForSingleObject(threads[killIdx], INFINITE);
        CloseHandle(threads[killIdx]);
        threads[killIdx] = NULL;
        activeThreads--;

        EnterCriticalSection(&printCS);
        std::cout << "После завершения маркера " << killId << ": ";
        for (int i = 0; i < arr.size(); ++i)
            std::cout << arr[i] << " ";
        std::cout << std::endl;
        LeaveCriticalSection(&printCS);


        for (int i = 0; i < n; ++i) {
            if (threads[i] != NULL) {
                ResetEvent(doneEvents[i]);
                SetEvent(params[i]->resumeEvent);
            }
        }
    }

    std::cout << "Все маркеры завершены." << std::endl;

    for (int i = 0; i < n; ++i) {
        if (threads[i]) CloseHandle(threads[i]);
        CloseHandle(doneEvents[i]);
        CloseHandle(params[i]->stopEvent);
        CloseHandle(params[i]->resumeEvent);
        delete params[i];
    }
    CloseHandle(startEvent);
    DeleteCriticalSection(&printCS);

    delete[] threads;
    delete[] params;
    delete[] doneEvents;

    return 0;
}
