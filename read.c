#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

#include "McuSystemPb.pb.h"
#include <pb_encode.h>
#include <pb_decode.h>

enum channels {
    SET_PREFERENCE = 372, // sync timestamp? PreferenceProvider.PreferenceBody
    MCU_REBOOT_RESPONSE = 395, // empty message
    MCU_REBOOT = 396, // McuSystemPb.reboot_reason
};

void send_message(int fd, int channel, int len, uint8_t *buf) {
    uint8_t b[4004];
    ((uint16_t*)b)[0] = channel;
    ((uint16_t*)b)[1] = len;
    memcpy(b + 4, buf, len);
    write(fd, b, len + 4);

    printf("TX: %d // ", channel);
    for(int i=0; i<(len + 4); i++)
        printf("%02hhx:", b[i]);
    printf("\n");
}

int main() {
    int fd = open("/dev/dcc_data", O_RDWR);
    uint8_t buf[4004];
    while(1) {
        int n = read(fd, buf, sizeof(buf));
        int channel = ((uint16_t*)buf)[0];
        int len = ((uint16_t*)buf)[1];
        if ((n-4) != len) printf("!!");
        printf("RX: %d // ", channel);
        for(int i=0; i<n; i++)
            printf("%02hhx:", buf[i]);
        printf("\n");

        if (channel == MCU_REBOOT) {
            McuSystemPb_reboot_reason message = McuSystemPb_reboot_reason_init_zero;
            pb_istream_t stream = pb_istream_from_buffer(buf + 4, len);
            int status = pb_decode(&stream, McuSystemPb_reboot_reason_fields, &message);
            printf("Protobuf decode returned %d, reason %d/%d, eStatus %d/%d\n",
                    status,
                    message.has_reason, message.reason,
                    message.has_eStatus, message.eStatus);
            if (message.has_mcuSysTime) {
                printf("...mcuSysTime timesource %d, type %d, time %d, timezone %d\n",
                        message.mcuSysTime.timeSource,
                        message.mcuSysTime.type,
                        message.mcuSysTime.time,
                        message.mcuSysTime.timezone);
            }
            // McuSystemPb.reboot_reason
            send_message(fd, MCU_REBOOT_RESPONSE, 0, buf);
        }
    }
}
