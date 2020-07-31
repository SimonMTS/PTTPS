#ifndef hex_helper_H
#define hex_helper_H

#include <iostream>
#include <string.h>

void print_hex(unsigned char* message) {

    for ( int i = 0; i < 32; i++ ) {
        if ( i % 2 == 0 ) std::cout << " ";
        std::cout << std::setfill('0') << std::setw(2) << std::hex << (int) message[i];

        if ( (i+1) % 4 == 0 ) {
            unsigned int number;
            memcpy(&number, &message[i-3], 4);

            printf(": %u \n", number);

        }
    }

}

#endif