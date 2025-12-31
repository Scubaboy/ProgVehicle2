#pragma once
#include "JsonPacketParser.h"
#include "JsonDefinitions.h"

using namespace PacketParser;
using namespace JsonTypeDefinitions;

class TelemetryPacketParser : public JsonPacketParser<TelemetryPacket>
{
    public:
        TelemetryPacket* Parse(char* packet, int size);
};