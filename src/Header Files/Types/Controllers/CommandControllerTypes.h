#pragma once
#include "JsonDefinitions.h"

using namespace JsonTypeDefinitions;

namespace CommandControllerDefinitions
{
    struct CommandCtrlType
    {
        PacketDataType Type;
        char* Command;
    };
}

