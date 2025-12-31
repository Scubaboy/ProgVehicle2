#pragma once
#include "JsonPacketParser.h"
#include "JsonDefinitions.h"

using namespace PacketParser;
using namespace JsonTypeDefinitions;

class ControlPacketParser : public JsonPacketParser<ControlPacket>
{
    public:
        ControlPacket* Parse(char* packet, int size);
};