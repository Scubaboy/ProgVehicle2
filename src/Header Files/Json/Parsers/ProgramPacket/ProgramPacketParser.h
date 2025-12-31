#pragma once
#include "JsonPacketParser.h"
#include "JsonDefinitions.h"

using namespace PacketParser;
using namespace JsonTypeDefinitions;

class ProgramPacketParser : public JsonPacketParser<ProgramPacket>
{
    public:
        ProgramPacket* Parse(char* packet, int size);
};