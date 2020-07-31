#ifndef pttps_base_socket_H
#define pttps_base_socket_H

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

    public:
    char* ip_address;
    int port;

    int setup() {

        if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\nSocket creation error \n");
            return -1;
        }
    
        struct sockaddr_in serv_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(this->port);
        
        if ( inet_pton(AF_INET, this->ip_address, &serv_addr.sin_addr) <= 0 )
        {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }
    
        if ( connect(this->sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0 ) 
        {
            printf("\nConnection Failed \n");
            return -1;
        }

        this->setup_complete = true;

    }
    
    bool send_msg(unsigned char* sent_message, unsigned char* received_message) {

        if ( !this->setup_complete ) {
            printf("\nSetup not complete \n");
            return false;
        }
        
        send( this->sock, sent_message, 32, 0 );
        read( this->sock, received_message, 32 );

        return true;

    }

};

#endif