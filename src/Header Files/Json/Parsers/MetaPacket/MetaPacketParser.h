#pragma once
#include "JsonPacketParser.h"
#include "JsonDefinitions.h"

using namespace PacketParser;
using namespace JsonTypeDefinitions;

class MetaPacketParser : public JsonPacketParser<MetaPacket>
{
    public:
        MetaPacket* Parse(char* packet, int size);
};