#include "MetaPacketParser.h"
#include "ArduinoJson-v7.4.2.h"

MetaPacket* MetaPacketParser::Parse(char* packet, int size)
{
    JsonDocument doc;
    //example json format
    //const char* test = "{\"type\":3,\"data\":\"{'type':0,'value':23}\"}";//\"{\"type\":0,\"data\":\"hello\"}\"}";
    DeserializationError error = deserializeJson(doc, packet);

    if (error)
    {
        printf("Json deserialization failed for MetaPacketParser - %s\n", packet);
        printf("Reason - %s \n",error.c_str());
        return nullptr;
    }

    int type = doc["type"];
    const char* data = doc["data"];
    auto test = static_cast<PacketDataType>(type);
    return new MetaPacket
    {
        test,
        (char*)data
    };
}