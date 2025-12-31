#pragma once
#include "ArduinoJson-v7.4.2.h"

namespace JsonTypeDefinitions
{
    enum PacketDataType
    {
        Program = 0,
        Telemetry = 1,
        Control = 2,
        Movement = 3
    };

    enum ControlAction
    {
        Stop,
        Manual,
        executePrograme
    };

    enum MovementType
    {
        Translation,
        Rotation
    };

    struct ControlPacket
    {
        ControlAction Action;
    };

    struct MovementPacket
    {
        MovementType Type;
        float Value;
    };
    
    struct ProgramPacket
    {
        int SequenceId;
        bool IsFinal;
        MovementPacket Action;
    };

    struct TelemetryPacket
    {
        float BatteryPercentage;
        float XRotation;
        float YRotation;
        float ZRotation;
    };

    struct MetaPacket
    {        
        PacketDataType Type;
        char* Data;     
    };

    inline void convertFromJson(JsonVariantConst src, MetaPacket& packet)
    {
        packet = src.as<MetaPacket>();
    };

    inline void convertFromJson(JsonVariantConst src, TelemetryPacket& packet)
    {
        packet = src.as<TelemetryPacket>();
    };

    inline void convertFromJson(JsonVariantConst src, ProgramPacket& packet)
    {
        packet = src.as<ProgramPacket>();
    };

    inline void convertFromJson(JsonVariantConst src, MovementPacket& packet)
    {
        packet = src.as<MovementPacket>();
    };
};