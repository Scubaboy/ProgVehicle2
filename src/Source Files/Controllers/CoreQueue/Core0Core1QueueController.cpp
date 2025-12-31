#include "Core0Core1QueueController.h"

using namespace Core0Core1QueueCtrl;

bool Core0Core1QueueController::IsQueueEmpty()
{
    return queue_is_empty(&_queue);
}

bool Core0Core1QueueController::TryEnqueue(const CommandCtrlType* item)
{
    return queue_try_add(&_queue, item);
}

bool Core0Core1QueueController::TryDequeue(CommandCtrlType* item)
{
    return queue_try_remove(&_queue, item);
}

