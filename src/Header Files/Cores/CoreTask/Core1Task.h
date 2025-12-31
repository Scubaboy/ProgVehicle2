#pragma once
#include "CoreTask.h"
#include "CoreQueue.h"
#include "CommandControllerTypes.h"

using namespace CoreTaskDefinition;
using namespace CoreQueueDefinition;
using namespace CommandControllerDefinitions;

namespace Core1TaskDefinition
{
    class Core1Task : CoreTask
    {
        public:
            Core1Task(CoreQueueRead<CommandCtrlType>* queue);
            void Task();
        private:
            CoreQueueRead<CommandCtrlType>* _readQueue;
    };
}