#pragma once
#include "CoreQueue.h"
#include "CommandControllerTypes.h"

using namespace CoreQueueDefinition;
using namespace CommandControllerDefinitions;

namespace CommandControllerProcessDefinition
{
    class CommandControllerProcess
    {
        public:
            virtual void Process(CoreQueueWrite<CommandCtrlType>* queue) = 0;
    };
}