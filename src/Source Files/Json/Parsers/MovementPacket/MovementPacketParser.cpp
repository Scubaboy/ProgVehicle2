#include "MovementPacketParser.h"
#include "ArduinoJson-v7.4.2.h"


MovementPacket* MovementPacketParser::Parse(char* packet, int size)
{
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, packet);

    if (error)
    {
        printf("Json deserialization failed for MovementPacketParser\n");
        printf("Reason - %s \n",error.c_str());
        return NULL;
    }

    auto packetData = doc.as<MovementPacket>();

    return new MovementPacket
    {
        packetData.Type,
        packetData.Value
    };
}