#ifndef pttps_base_socket_H
#define pttps_base_socket_H

#include <stdio.h> 
#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <iomanip>
#include <iostream>

class pttps_base_server {

    private:
    bool setup_complete = false;
    int server_fd;
    int addrlen;
    struct sockaddr_in address;
    int new_socket;

    public:
    int port;

    int setup() {

        int opt = 1;
        this->addrlen = sizeof(this->address);
        
        // Creating socket file descriptor
        if ( (this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0 )
        {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }
        
        // Forcefully attaching socket to the port 8080
        if ( setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) )
        {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }
        this->address.sin_family = AF_INET;
        this->address.sin_addr.s_addr = INADDR_ANY;
        this->address.sin_port = htons( this->port );
        
        // Forcefully attaching socket to the port 8080
        if ( bind(this->server_fd, (struct sockaddr *)&this->address, sizeof(this->address)) < 0 )
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        if ( listen(this->server_fd, 3) < 0 )
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }

        this->setup_complete = true;

    }

    int listener_setup( std::function<void(unsigned char*)> callback ) {

        if ( !this->setup_complete ) {
            printf("\nSetup not complete \n");
            return false;
        }

        unsigned char buffer[32] = {0};
        while(true) {
            if ( (this->new_socket = accept(this->server_fd, (struct sockaddr *)&this->address,   (socklen_t*)&this->addrlen)) < 0 ) 
            { 
                perror("accept"); 
                exit(EXIT_FAILURE); 
            } 

            memset(buffer, 0, sizeof buffer);

            read( this->new_socket , buffer, 32); 

            if ( buffer[0] == 0x00 ) {
                std::cout << "\nReceived stop msg\n"; 
                return 0;
            }

            callback( buffer );

        }

    }

    void send_msg(unsigned char* message) {
        
        send( this->new_socket , message , 32 , 0 ); 

    }

};

#endif