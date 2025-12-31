#include <stdio.h>
#include "pico/stdlib.h"
#include "BluetoothComms.h"
#include "MetaPacketParser.h"
#include "CommandController.h"
#include "CommandControllerTypes.h"
#include "Core0Core1QueueController.h"
#include "Core0Task.h"
#include "Core1Task.h"
#include "pico/multicore.h"

using namespace CommandControllerDefinitions;
using namespace CommandCtrl;
using namespace PacketParser;
using namespace Bluetooth;
using namespace Core0Core1QueueCtrl;
using namespace Core0TaskDefinition;
using namespace Core1TaskDefinition;

MetaPacketParser metaPacketParser;
CommandController commandController;
Core0Core1QueueController core0Core1QueueCtrl;
Core0Task core0Task(&core0Core1QueueCtrl, &commandController);
Core1Task core1Task(&core0Core1QueueCtrl);

void Core1_Main()
{
    core1Task.Task();
}

void BluetoothPacketReceiver(char *packet, short unsigned int size)
{
    auto result = metaPacketParser.Parse(packet, size);
    auto command = new CommandCtrlType();

    command->Command = result->Data;
    command->Type = result->Type;
     commandController.QueueCommand(command);

    delete result;
}

int main()
{
    //Initialise stdio
    stdio_init_all();
    //Initialise core queues
    core0Core1QueueCtrl.Initialise();
    //Initialise bluetooth
    BluetoothComms::SppServiceSetup(BluetoothPacketReceiver);
     //Launch core1 task
    multicore_launch_core1(Core1_Main);
    //Launch core0 task
    core0Task.Task();
}
