#include "BluetoothComms.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/cyw43_arch.h"

using namespace Bluetooth;

#define RFCOMM_SERVER_CHANNEL 1
#define HEARTBEAT_PERIOD_MS 1000

btstack_packet_callback_registration_t BluetoothComms::hci_event_callback_registration;
uint16_t BluetoothComms::rfcomm_channel_id;
uint8_t  BluetoothComms::spp_service_buffer[150];
btstack_timer_source_t BluetoothComms::heartbeat;
char BluetoothComms::lineBuffer[30];
PTR BluetoothComms::packetHandler;

void BluetoothComms::SppServiceSetup(PTR packetHandlerInput)
{
    // Initialise the Wi-Fi\Bluetooth chip
    if (cyw43_arch_init()) {
        printf("cyw43_arch_init() failed.\n");
        return;
    }

    BluetoothComms::one_shot_timer_setup();

    BluetoothComms::packetHandler = packetHandlerInput;

    // register for HCI events
    BluetoothComms::hci_event_callback_registration.callback = &BluetoothComms::PacketHandler;
    hci_add_event_handler(&BluetoothComms::hci_event_callback_registration);

    l2cap_init();

#ifdef ENABLE_BLE
    // Initialize LE Security Manager. Needed for cross-transport key derivation
    sm_init();
#endif

    rfcomm_init();
    rfcomm_register_service(BluetoothComms::PacketHandler, RFCOMM_SERVER_CHANNEL, 0xffff);  // reserved channel, mtu limited by l2cap

    // init SDP, create record for SPP and register with SDP
    sdp_init();
    memset(BluetoothComms::spp_service_buffer, 0, sizeof(BluetoothComms::spp_service_buffer));
    spp_create_sdp_record(BluetoothComms::spp_service_buffer, 0x10001, RFCOMM_SERVER_CHANNEL, "SPP Counter");
    sdp_register_service(BluetoothComms::spp_service_buffer);

    gap_discoverable_control(1);
    gap_ssp_set_io_capability(SSP_IO_CAPABILITY_DISPLAY_YES_NO);
    gap_set_local_name("SPP Counter 00:00:00:00:00:00");

    // turn on!
    hci_power_control(HCI_POWER_ON);
    printf("SDP service record size: %u\n", de_get_len(BluetoothComms::spp_service_buffer));
}

void BluetoothComms::heartbeat_handler(struct btstack_timer_source *ts)
{
    static int counter = 0;

   // if (BluetoothComms::rfcomm_channel_id){
   //     snprintf(BluetoothComms::lineBuffer, sizeof(BluetoothComms::lineBuffer), "BTstack counter %04u\n", ++counter);
   //     printf("%s", BluetoothComms::lineBuffer);

        //rfcomm_request_can_send_now_event(BluetoothComms::rfcomm_channel_id);
   // }

    btstack_run_loop_set_timer(ts, HEARTBEAT_PERIOD_MS);
    btstack_run_loop_add_timer(ts);
} 

void BluetoothComms::one_shot_timer_setup()
{
    // set one-shot timer
    heartbeat.process = &BluetoothComms::heartbeat_handler;
    btstack_run_loop_set_timer(&BluetoothComms::heartbeat, HEARTBEAT_PERIOD_MS);
    btstack_run_loop_add_timer(&BluetoothComms::heartbeat);
}

void BluetoothComms::PacketHandler (unsigned char packet_type, short unsigned int channel, unsigned char *packet, short unsigned int size)
{
    UNUSED(channel);

/* LISTING_PAUSE */ 
    bd_addr_t event_addr;
    uint8_t   rfcomm_channel_nr;
    uint16_t  mtu;
    int i;

    switch (packet_type) {
        case HCI_EVENT_PACKET:
            switch (hci_event_packet_get_type(packet)) {
/* LISTING_RESUME */ 
                case HCI_EVENT_PIN_CODE_REQUEST:
                    // inform about pin code request
                    printf("Pin code request - using '0000'\n");
                    hci_event_pin_code_request_get_bd_addr(packet, event_addr);
                    gap_pin_code_response(event_addr, "0000");
                    break;

                case HCI_EVENT_USER_CONFIRMATION_REQUEST:
                    // ssp: inform about user confirmation request
                    printf("SSP User Confirmation Request with numeric value '%06" PRIu32 "'\n", little_endian_read_32(packet, 8));
                    printf("SSP User Confirmation Auto accept\n");
                    break;

                case RFCOMM_EVENT_INCOMING_CONNECTION:
                    rfcomm_event_incoming_connection_get_bd_addr(packet, event_addr);
                    rfcomm_channel_nr = rfcomm_event_incoming_connection_get_server_channel(packet);
                    BluetoothComms::rfcomm_channel_id = rfcomm_event_incoming_connection_get_rfcomm_cid(packet);
                    printf("RFCOMM channel %u requested for %s\n", rfcomm_channel_nr, bd_addr_to_str(event_addr));
                    rfcomm_accept_connection(BluetoothComms::rfcomm_channel_id);
                    break;
               
                case RFCOMM_EVENT_CHANNEL_OPENED:
                    if (rfcomm_event_channel_opened_get_status(packet)) {
                        printf("RFCOMM channel open failed, status %u\n", rfcomm_event_channel_opened_get_status(packet));
                    } else {
                        BluetoothComms::rfcomm_channel_id = rfcomm_event_channel_opened_get_rfcomm_cid(packet);
                        mtu = rfcomm_event_channel_opened_get_max_frame_size(packet);
                        printf("RFCOMM channel open succeeded. New RFCOMM Channel ID %u, max frame size %u\n", BluetoothComms::rfcomm_channel_id, mtu);
                    }
                    break;
                case RFCOMM_EVENT_CAN_SEND_NOW:
                    rfcomm_send(BluetoothComms::rfcomm_channel_id, (uint8_t*) BluetoothComms::lineBuffer, (uint16_t) strlen(BluetoothComms::lineBuffer));  
                    break;

/* LISTING_PAUSE */                 
                case RFCOMM_EVENT_CHANNEL_CLOSED:
                    printf("RFCOMM channel closed\n");
                    BluetoothComms::rfcomm_channel_id = 0;
                    break;
                
                default:
                    break;
            }
            break;

        case RFCOMM_DATA_PACKET:
        {
            (*BluetoothComms::packetHandler)((char*)(packet), size); 
            break;
        }
        default:
            break;
    }
}