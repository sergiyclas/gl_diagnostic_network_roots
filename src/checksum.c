#include "checksum.h"

uint16_t checksum(void* packet, int length)
{
        uint16_t* buff = (uint16_t*)packet;
        uint32_t sum = 0;
        uint16_t result;

        for(; length > 1; length -= 2)
        {
                sum+= *buff++;
        }
        if(length == 1)
        {
                sum+= *(unsigned char*)buff;
        }
        sum = (sum >> 16) + (sum & 0xFFFF);
        sum += (sum >> 16);
        result = ~sum;

        return result;
}
