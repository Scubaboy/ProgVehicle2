#pragma once
#include "CoreTask.h"
#include "CoreQueue.h"
#include "CommandControllerTypes.h"
#include "CommandControllerProcess.h"

using namespace CoreTaskDefinition;
using namespace CoreQueueDefinition;
using namespace CommandControllerDefinitions;
using namespace CommandControllerProcessDefinition;

namespace Core0TaskDefinition
{
    class Core0Task : CoreTask
    {
        public:
            Core0Task(CoreQueueWrite<CommandCtrlType>* queue, CommandControllerProcess* commandControllerProcess);
            void Task();
        private:
            CoreQueueWrite<CommandCtrlType>* _writeQueue; 
            CommandControllerProcess* _commandControllerProcess;
    };
}