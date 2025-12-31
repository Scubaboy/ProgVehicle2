#pragma once
#include "JsonPacketParser.h"
#include "JsonDefinitions.h"

using namespace PacketParser;
using namespace JsonTypeDefinitions;

class MovementPacketParser : public JsonPacketParser<MovementPacket>
{
    public:
        MovementPacket* Parse(char* packet, int size);
};