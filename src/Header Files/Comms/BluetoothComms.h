#pragma once
#include "btstack.h"
#include <inttypes.h>
#include "TypeDefinitions.h"


namespace Bluetooth
{
    class BluetoothComms
    {
        public:
            static void SppServiceSetup(PTR packetHandler);
        private:
            static void one_shot_timer_setup(void);
            static void PacketHandler (unsigned char packet_type, short unsigned int channel, unsigned char *packet, short unsigned int size);
            static void heartbeat_handler(struct btstack_timer_source *ts);
            static btstack_packet_callback_registration_t hci_event_callback_registration;
            static uint16_t rfcomm_channel_id;
            static uint8_t  spp_service_buffer[150];
            static btstack_timer_source_t heartbeat;
            static char lineBuffer[30];
            static PTR packetHandler;
    };
} 