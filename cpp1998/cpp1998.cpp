#include <windows.h>
#include <iostream>
#include <vector>
#include "marker_thread.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
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
    HANDLE stopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    HANDLE resumeEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    
    for (int i = 0; i < n; ++i) {
        doneEvents[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
        params[i] = new MarkerParams;
        params[i]->id = i + 1;
        params[i]->array = &arr;
        params[i]->startEvent = startEvent;
        params[i]->stopEvent = stopEvent;
        params[i]->resumeEvent = resumeEvent;
        params[i]->doneEvent = doneEvents[i];
        threads[i] = CreateThread(NULL, 0, MarkerThread, params[i], 0, NULL);
    }

    SetEvent(startEvent);

    int activeThreads = n;
    bool running = true;

    while (running && activeThreads > 0) {
        DWORD result = WaitForMultipleObjects(n, doneEvents, FALSE, INFINITE);

        if (result >= WAIT_OBJECT_0 && result < WAIT_OBJECT_0 + n) {
            int idx = result - WAIT_OBJECT_0;


            ResetEvent(doneEvents[idx]);

            std::cout << "Состояние массива: ";
            for (int i = 0; i < arr.size(); ++i) {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;

            std::cout << "Остановка маркера " << params[idx]->id << std::endl;


            SetEvent(stopEvent);
            WaitForSingleObject(threads[idx], INFINITE);
            CloseHandle(threads[idx]);
            threads[idx] = NULL;
            activeThreads--;


            if (activeThreads == 0) {
                running = false;
            }
            else {
                
                ResetEvent(stopEvent);
                SetEvent(resumeEvent);
                ResetEvent(resumeEvent);
            }
        }
    }

    std::cout << "Итоговый массив: ";
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;


    for (int i = 0; i < n; ++i) {
        if (threads[i]) {
            CloseHandle(threads[i]);
        }
        CloseHandle(doneEvents[i]);
        delete params[i];
    }

    CloseHandle(startEvent);
    CloseHandle(stopEvent);
    CloseHandle(resumeEvent);

    delete[] threads;
    delete[] params;
    delete[] doneEvents;

    return 0;
}