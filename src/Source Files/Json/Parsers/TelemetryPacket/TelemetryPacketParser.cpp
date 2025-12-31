#include "TelemetryPacketParser.h"
#include "ArduinoJson-v7.4.2.h"


TelemetryPacket* TelemetryPacketParser::Parse(char* packet, int size)
{
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, packet);

    if (error)
    {
        printf("Json deserialization failed for TelemetryPacketParser\n");
        printf("Reason - %s \n",error.c_str());
        return NULL;
    }

    auto packetData = doc.as<TelemetryPacket>();

    return new TelemetryPacket
    {
        packetData.BatteryPercentage,
        packetData.XRotation,
        packetData.YRotation,
        packetData.ZRotation
    };
}