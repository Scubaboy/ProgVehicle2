#pragma once
#include "CoreQueue.h"
#include "CommandControllerTypes.h"
#include "pico/util/queue.h"

using namespace CoreQueueDefinition;
using namespace CommandControllerDefinitions;

namespace Core0Core1QueueCtrl
{
    class Core0Core1QueueController : public CoreQueueWrite<CommandCtrlType>, public CoreQueueRead<CommandCtrlType>
    {
        public:
            void Initialise()
            {
                queue_init(&_queue, sizeof(CommandCtrlType), 10);
            };
            bool TryEnqueue(const CommandCtrlType* item); 
            bool TryDequeue(CommandCtrlType* item); 
            bool IsQueueEmpty();
        private:
         queue_t _queue;
    };
}