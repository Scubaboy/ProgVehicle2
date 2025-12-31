#include "ControlPacketParser.h"
#include "ArduinoJson-v7.4.2.h"

ControlPacket* ControlPacketParser::Parse(char* packet, int size)
{
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, packet);

    if (error)
    {
        printf("Json deserialization failed for ControlPacketParser\n");
        printf("Reason - %s \n",error.c_str());
        return NULL;
    }

    return new ControlPacket
    {
        doc["Action"]
    };
}