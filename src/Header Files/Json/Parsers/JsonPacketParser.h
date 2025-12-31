#pragma once

namespace PacketParser
{  
    template <typename T>  
    class JsonPacketParser
    {
        public:
            virtual T* Parse(char* packet, int size) = 0; //Pure virtual function
    };
}