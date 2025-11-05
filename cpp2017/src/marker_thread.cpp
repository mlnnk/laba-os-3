#include "marker_thread.h"
#include <iostream>

DWORD WINAPI MarkerThread(LPVOID param) {
    MarkerParams* p = static_cast<MarkerParams*>(param);
    MarkerLogic logic(p->id, static_cast<int>(p->array->size()));

    WaitForSingleObject(p->startEvent, INFINITE);

    while (true) {
        if (WaitForSingleObject(p->stopEvent, 0) == WAIT_OBJECT_0)
            break;

        int blockedIndex = -1;
        bool success = logic.step(*p->array, blockedIndex);

        if (success) {
            continue;
        }
        else {
            
            EnterCriticalSection(p->printCS);
            std::cout << "ћаркер " << p->id
                << " заблокирован на индексе " << blockedIndex
                << ", помечено: " << logic.getMarkedCount()
                << std::endl;
            LeaveCriticalSection(p->printCS);

            SetEvent(p->doneEvent);

            HANDLE events[2] = { p->resumeEvent, p->stopEvent };
            DWORD waitResult = WaitForMultipleObjects(2, events, FALSE, INFINITE);

            if (waitResult == WAIT_OBJECT_0 + 1)
                break;
        }
    }

    
    for (auto& v : *p->array)
        if (v == p->id) v = 0;

    return 0;
}
