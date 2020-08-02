#ifndef pttps_base_socket_H
#define pttps_base_socket_H

#include <hex_helper.cpp>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <iomanip>

class pttps_base_client {

    private:
    int sock = 0;
    bool setup_complete = false;
    char* ip_address;
    int port;

    public:
    pttps_base_client(char* ip_address, int port) {

        this->ip_address = ip_address;
        this->port = port;


        if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\nSocket creation error \n");
            exit(EXIT_FAILURE);
        }
    
        struct sockaddr_in serv_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(this->port);
        
        if ( inet_pton(AF_INET, this->ip_address, &serv_addr.sin_addr) <= 0 )
        {
            printf("\nInvalid address/ Address not supported \n");
            exit(EXIT_FAILURE);
        }
    
        if ( connect(this->sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0 ) 
        {
            printf("\nConnection Failed \n");
            exit(EXIT_FAILURE);
        }

        this->setup_complete = true;

    }
    
    bool send_dh_msg(unsigned char* sent_message, unsigned char* received_message) {

        if ( !this->setup_complete ) {
            printf("\nSetup not complete \n");
            return false;
        }

        print_hex_DH_sent(sent_message);
        
        send( this->sock, sent_message, 20, 0 );
        read( this->sock, received_message, 20 );

        print_hex_DH_received(received_message);

        return true;

    }
    
    bool send_encrypted_msg(unsigned char* sent_message, unsigned char* received_message) {

        if ( !this->setup_complete ) {
            printf("\nSetup not complete \n");
            return false;
        }

        print_hex_encrypted_sent(sent_message);
        
        send( this->sock, sent_message, 20, 0 );

        return true;

    }

    bool send_stop_msg() {

        if ( !this->setup_complete ) {
            printf("\nSetup not complete \n");
            return false;
        }

        unsigned char sent_message[20] = {0xff};
        for ( int i = 0; i < 20; i = i+4 ) {
            sent_message[i  ] = 'S';
            sent_message[i+1] = 'T';
            sent_message[i+2] = 'O';
            sent_message[i+3] = 'P';
        }

        print_hex_STOP_sent(sent_message);
        
        send( this->sock, sent_message, 20, 0 );

        return true;

    }

};

#endif