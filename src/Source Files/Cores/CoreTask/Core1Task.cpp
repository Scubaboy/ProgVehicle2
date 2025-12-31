#include "Core1Task.h"
#include "pico/stdlib.h"

using namespace Core1TaskDefinition;

Core1Task::Core1Task(CoreQueueRead<CommandCtrlType>* queue)
{
    _readQueue = queue;
}

void Core1Task::Task()
{
    while (true) 
    { 
        CommandCtrlType command;

        if (!_readQueue->IsQueueEmpty() && _readQueue->TryDequeue(&command))
        {
            printf("Command received from Core 0 %d command data %s\n", command.Type, command.Command);
        }    

        sleep_ms(1000);
    }
}