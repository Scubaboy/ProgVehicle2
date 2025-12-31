#include "ProgramPacketParser.h"
#include "ArduinoJson-v7.4.2.h"


ProgramPacket* ProgramPacketParser::Parse(char* packet, int size)
{
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, packet);

    if (error)
    {
        printf("Json deserialization failed for ProgramPacketParser\n");
        printf("Reason - %s \n",error.c_str());
        return NULL;
    }

    auto packetData = doc.as<ProgramPacket>();

    return new ProgramPacket
    {
        packetData.SequenceId,
        packetData.IsFinal,
        packetData.Action
    };
}