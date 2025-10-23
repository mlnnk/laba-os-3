#include "marker_thread.h"
#include <iostream>

DWORD WINAPI MarkerThread(LPVOID param) {
    MarkerParams* p = static_cast<MarkerParams*>(param);
    MarkerLogic logic(p->id, static_cast<int>(p->array->size()));

    WaitForSingleObject(p->startEvent, INFINITE);

    while (true) {
       
        if (WaitForSingleObject(p->stopEvent, 0) == WAIT_OBJECT_0) {
            break;
        }

        bool success = logic.step(*p->array);
        if (success) {
            Sleep(5);
        }
        else {
            std::cout << "Маркер " << p->id
                << " заблокирован, помечено: " << logic.getMarkedCount()
                << std::endl;

            SetEvent(p->doneEvent);

           
            HANDLE events[2] = { p->resumeEvent, p->stopEvent };
            DWORD waitResult = WaitForMultipleObjects(2, events, FALSE, INFINITE);

            if (waitResult == WAIT_OBJECT_0 + 1) { 
                break;
            }
         
        }
    }
    for (int i = 0; i < p->array->size(); ++i) {
        if ((*p->array)[i] == p->id) {
            (*p->array)[i] = 0;
        }
    }

    return 0;
}