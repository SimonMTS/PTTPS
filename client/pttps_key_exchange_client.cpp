#ifndef pttps_key_exchange_H
#define pttps_key_exchange_H

#include <client/pttps_base_client.cpp>
#include <diffie_hellmann_helper.cpp>
#include <random>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <gmp.h>

class pttps_key_exchange_client {

    private:
    pttps_base_client* base_client;

    public:
    pttps_key_exchange_client(pttps_base_client* base_client) {

        this->base_client = base_client;

    }

    unsigned int generate_key() {

        unsigned int list[5] = { 0, 0, 0, 0, 0 };
        diffie_hellmann_helper DHH;
        DHH.generate_request_variables(list);

        this->exchange_numbers(list);

        unsigned int shared_key = DHH.calc_shared_key(list, list[4]);

        print_hex_DH_received_followup(list[2], list[3], shared_key);

        return shared_key;
        
    }

    private:
    void exchange_numbers(unsigned int* list) {

        unsigned char sent_message[20] = {0xff};
        std::fill_n(sent_message, 20, 0xff);
        sent_message[0] = 'D';
        sent_message[1] = 'H';
        sent_message[2] = 'K';
        sent_message[3] = 'E';

        memcpy(&sent_message[ 4], &list[0], 4);
        memcpy(&sent_message[ 8], &list[1], 4);
        memcpy(&sent_message[12], &list[3], 4);

        unsigned char received_message[20] = {0};
        bool success = (*this->base_client).send_dh_msg( sent_message, received_message );

        memcpy(&list[4], &received_message[16], 4);

    }

};

#endif