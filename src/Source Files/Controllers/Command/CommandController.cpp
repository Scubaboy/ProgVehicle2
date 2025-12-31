#include "CommandController.h"

using namespace CommandCtrl;
using namespace JsonTypeDefinitions;

void CommandController::QueueCommand(CommandCtrlType* commandCtrlType)
{
    _buffer.Append(commandCtrlType);
}

void CommandController::Process(CoreQueueWrite<CommandCtrlType>* queue)
{
   if (_buffer.IsEmpty()) 
   {
        return;
   }

   auto command = _buffer.Read();

   if (command != nullptr)
   {
        switch (command->Type)
        {
                case PacketDataType::Control:
                {
                    queue->TryEnqueue(command);
                    break;
                }
                case PacketDataType::Movement:
                {
                    queue->TryEnqueue(command);
                    break;
                }
                case PacketDataType::Program:
                {
                    break;
                }
                case PacketDataType::Telemetry:
                {
                    break;
                }
        }
    }
}