#ifndef pttps_encrypted_msg_client_H
#define pttps_encrypted_msg_client_H

#include <feistel_network_encryption_helper.cpp>
#include <math.h>

class pttps_encrypted_msg_client {

    private:
    pttps_base_client* base_client;
    unsigned int key;

    public:
    pttps_encrypted_msg_client(pttps_base_client* base_client, unsigned int key) {

        this->base_client = base_client;
        this->key = key;

    }

    void send_msg(char* msg, int str_len) {

        int number_of_msg = ceil(((str_len - 1) / 16) + 0.5);

        unsigned char buffer[16] = {0};
        for ( int i = 0; i < number_of_msg; i++ ) {

            std::fill_n(buffer, 16, '\0');
            int buffer_size = i+1 == number_of_msg ? (str_len % 16 == 0 ? 16 : str_len % 16) : 16;
            memcpy(&buffer[0], &msg[i*16], buffer_size);

            this->send_msg_packet(buffer);

        }

    }

    void send_msg_packet(unsigned char* msg) {

        unsigned char sent_message[20] = {0xff};
        std::fill_n(sent_message, 20, 0xff);
        sent_message[0] = 'E';
        sent_message[1] = 'N';
        sent_message[2] = 'C';
        sent_message[3] = 'R';

        memcpy(&sent_message[4], &msg[0], 16);
        print_hex_plaintext_msg( sent_message );

        srand(this->key);
        unsigned int key_array[feistel_network_encryption_helper::number_of_feistel_rounds];
        for ( int i = 0; i < feistel_network_encryption_helper::number_of_feistel_rounds; i++ ) {
            key_array[i] = rand();
        }

        feistel_network_encryption_helper::apply_feistel_network_pass(msg, key_array);

        memcpy(&sent_message[4], &msg[0], 16);

        unsigned char received_message[20] = {0};
        bool success = (*this->base_client).send_encrypted_msg( sent_message, received_message );

    }
  
};

#endif