#ifndef pttps_key_exchange_H
#define pttps_key_exchange_H

#include <client/pttps_base_client.cpp>
#include <diffie_hellmann_helper.cpp>
#include <hex_helper.cpp>
#include <random>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <gmp.h>

class pttps_key_exchange_client {

    private:
    pttps_base_client pttps_client;

    public:
    pttps_key_exchange_client(char* ip) {

        pttps_client.ip_address = ip;
        pttps_client.port = 8080;

        pttps_client.setup();

    }

    unsigned int generate_key() {

        unsigned int list[5] = { 0, 0, 0, 0, 0 };
        diffie_hellmann_helper DHH;
        DHH.generate_request_variables(list);

        this->exchange_numbers(list);

        
        printf("\nPrivate_key: %llu\n", list[2]);

        return DHH.calc_shared_key(list, list[4]);
        
    }

    private:
    void exchange_numbers(unsigned int* list) {

        unsigned char sent_message[32] = {0xff};
        std::fill_n(sent_message, 32, 0xff);

        memcpy(&sent_message[ 4], &list[0], 4);
        memcpy(&sent_message[ 8], &list[1], 4);
        memcpy(&sent_message[12], &list[3], 4);

        unsigned char received_message[32] = {0};
        bool success = pttps_client.send_msg( sent_message, received_message );

        memcpy(&list[4], &received_message[16], 4);

        if ( success ) {
            std::cout << "Sent msg:\n";
            print_hex(sent_message);

            std::cout << "\n\nReceived msg:\n";
            print_hex(received_message);
            std::cout << "\n";
        }

    }

};

#endif