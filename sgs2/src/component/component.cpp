#include "component.h"

void component::process_task()
{
    task t;
    while (q_.try_pop(t))
    {
        t();
    }
}