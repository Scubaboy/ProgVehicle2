#include "Core0Task.h"
#include "pico/stdlib.h"

using namespace Core0TaskDefinition;

Core0Task::Core0Task(CoreQueueWrite<CommandCtrlType>* queue, CommandControllerProcess* commandControllerProcess)
{
    _writeQueue = queue;
    _commandControllerProcess = commandControllerProcess;
}

void Core0Task::Task()
{
    while (true) 
    {        
        _commandControllerProcess->Process(_writeQueue);
        sleep_ms(1000);
    }
}