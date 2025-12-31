#pragma once
#include "CommandControllerTypes.h"
#include "CircularBuffer.h"
#include "CommandControllerProcess.h"

using namespace CommandControllerProcessDefinition;
using namespace CommandControllerDefinitions;
using namespace CircularBufferDefition;

namespace CommandCtrl
{
    class CommandController : public CommandControllerProcess
    {
        public:
            void QueueCommand(CommandCtrlType* commandCtrlType);
            void Process(CoreQueueWrite<CommandCtrlType>* queue);
        private:
            CircularBuffer<100, CommandCtrlType> _buffer;

    };
}