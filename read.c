#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

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

    printf("TX: ");
    for(int i=0; i<(len + 4); i++)
        printf("%02hhx:", b[i]);
    printf("\n");
}

int main() {
    int fd = open("/dev/dcc_data", O_RDWR);
    uint8_t buf[4004];
    while(1) {
        int n = read(fd, buf, sizeof(buf));
        int channel = *((uint16_t*)buf);
        printf("RX: %d // ", channel);
        for(int i=0; i<n; i++)
            printf("%02hhx:", buf[i]);
        printf("\n");

        if (channel == MCU_REBOOT) {
            // McuSystemPb.reboot_reason
            send_message(fd, MCU_REBOOT_RESPONSE, 0, buf);
        }
    }
}
