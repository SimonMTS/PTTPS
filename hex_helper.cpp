#ifndef hex_helper_H
#define hex_helper_H

#include <iostream>
#include <string.h>
#include <iomanip>
#include <cmath>
#include <algorithm>

void print_hex(unsigned char* message) {

    std::cout << "|";
    for ( int i = 0; i < 32; i++ ) {
        if ( i % 2 == 0 ) std::cout << " ";
        std::cout << std::setfill('0') << std::setw(2) << std::hex << (int) message[i];

        if ( (i+1) % 4 == 0 ) {
            unsigned int number; memcpy(&number, &message[i-3], 4);

            printf(": %u \n|", number);

        }
    }

}

void print_hex_DH_sent(unsigned char* message) {

    int i = 0;
    unsigned int number;

    std::cout << std::endl;
    std::cout << "\u001b[34;1m <- |" << "_Diffie_Hellmann_Key_Exchange______" << std::endl;
    std::cout << "\u001b[34;1m <- |" << "__Hex________:__Decimal___:__Char__" << std::endl;

    for ( int n = 0; n < 5; n++ ) {

        std::cout << "\u001b[34;1m <- |\u001b[0m";

        for ( int j = i; i < j+4; i++ ) {
            std::cout << " " << std::setfill('0') << std::setw(2) << std::hex << (int) message[i];
        }
        
        memcpy(&number, &message[i-4], 4);

        if ( number != std::numeric_limits<unsigned int>::max() && number != std::numeric_limits<unsigned int>::min() ) {

            if (n != 0)
                printf(" :\u001b[34;1m % 10u \u001b[0m: ", number);
            else
                printf(" : % 10u : ", number);

            if ( n == 0 ) {
                std::cout << (char) message[i-4] << " ";
                std::cout << (char) message[i-3] << " ";
                std::cout << (char) message[i-2] << " ";
                std::cout << (char) message[i-1] << " ";
            } else {
                std::cout << "        ";    
            }

        } else {
            std::cout << " :            :         ";
        }

        switch(n) {
            case 0: std::cout << "\u001b[30;1m// Packet description\u001b[0m"; break;
            case 1: std::cout << "\u001b[30;1m// N, random large prime number\u001b[0m"; break;
            case 2: std::cout << "\u001b[30;1m// G, random large prime number, smaller then N\u001b[0m"; break;
            case 3: std::cout << "\u001b[30;1m// A, Client public key\u001b[0m"; break;
            case 4: std::cout << "\u001b[30;1m// B, Server public key\u001b[0m"; break;
        }
        
        std::cout << std::endl;

    }
    
}

void print_hex_DH_received(unsigned char* message) {

    int i = 0;
    unsigned int number;

    std::cout << std::endl;
    std::cout << "\u001b[36;1m -> |" << "_Diffie_Hellmann_Key_Exchange______" << std::endl;
    std::cout << "\u001b[36;1m -> |" << "__Hex________:__Decimal___:__Char__" << std::endl;

    for ( int n = 0; n < 5; n++ ) {

        std::cout << "\u001b[36;1m -> |\u001b[0m";

        for ( int j = i; i < j+4; i++ ) {
            std::cout << " " << std::setfill('0') << std::setw(2) << std::hex << (int) message[i];
        }
        
        memcpy(&number, &message[i-4], 4);

        if ( number != std::numeric_limits<unsigned int>::max() && number != std::numeric_limits<unsigned int>::min() ) {

            if (n != 0)
                printf(" :\u001b[36;1m % 10u \u001b[0m: ", number);
            else
                printf(" : % 10u : ", number);

            if ( n == 0 ) {
                std::cout << (char) message[i-4] << " ";
                std::cout << (char) message[i-3] << " ";
                std::cout << (char) message[i-2] << " ";
                std::cout << (char) message[i-1] << " ";
            } else {
                std::cout << "        ";    
            }

        } else {
            std::cout << " :            :         ";
        }

        switch(n) {
            case 0: std::cout << "\u001b[30;1m// Packet description\u001b[0m"; break;
            case 1: std::cout << "\u001b[30;1m// N, random large prime number\u001b[0m"; break;
            case 2: std::cout << "\u001b[30;1m// G, random large prime number, smaller then N\u001b[0m"; break;
            case 3: std::cout << "\u001b[30;1m// A, Client public key\u001b[0m"; break;
            case 4: std::cout << "\u001b[30;1m// B, Server public key\u001b[0m"; break;
        }
        
        std::cout << std::endl;

    }

}

void print_hex_DH_received_followup(unsigned int private_key, unsigned int public_key, unsigned int shared_key) {

    std::cout << "\u001b[36;1m -> |\u001b[0m" << std::endl;
    std::cout << "\u001b[36;1m -> |\u001b[0m" << " Private key: "; printf("%llu\n", private_key);
    std::cout << "\u001b[36;1m -> |\u001b[0m" << "  Public key: "; printf("%llu\n", public_key);
    std::cout << "\u001b[36;1m -> |\u001b[0m" << "  Shared key: "; printf("%llu\n", shared_key);

}


void print_hex_SP_sent(unsigned char* message) {

    int i = 0;
    unsigned int number;

    std::cout << std::endl;
    std::cout << "\u001b[33;1m <- |" << "_SP_Network_Encrypted_Message______" << std::endl;
    std::cout << "\u001b[33;1m <- |" << "__Hex________:__Decimal___:__Char__" << std::endl;

    for ( int n = 0; n < 5; n++ ) {

        std::cout << "\u001b[33;1m <- |\u001b[0m";

        for ( int j = i; i < j+4; i++ ) {
            std::cout << " " << std::setfill('0') << std::setw(2) << std::hex << (int) message[i];
        }
        
        memcpy(&number, &message[i-4], 4);

        if ( number != std::numeric_limits<unsigned int>::max() && number != std::numeric_limits<unsigned int>::min() ) {

            printf(" : % 10u : ", number);

            if (n != 0)
                std::cout << "\u001b[33;1m";

            if ( n == 0 ) {
                std::cout << (char) message[i-4] << " ";
                std::cout << (char) message[i-3] << " ";
                std::cout << (char) message[i-2] << " ";
                std::cout << (char) message[i-1] << "\u001b[0m ";
            } else {
                std::cout << "        ";    
            }

        } else {
            std::cout << " :            :         ";
        }

        switch(n) {
            case 0: std::cout << "\u001b[30;1m// Packet description\u001b[0m"; break;
            case 1: std::cout << "\u001b[30;1m// Message data\u001b[0m"; break;
            case 2: std::cout << "\u001b[30;1m// Message data\u001b[0m"; break;
            case 3: std::cout << "\u001b[30;1m// Message data\u001b[0m"; break;
            case 4: std::cout << "\u001b[30;1m// Message data\u001b[0m"; break;
        }
        
        std::cout << std::endl;

    }
    
}

void print_hex_SP_received(unsigned char* message) {

    int i = 0;
    unsigned int number;

    std::cout << std::endl;
    std::cout << "\u001b[35;1m -> |" << "_SP_Network_Encrypted_Message______" << std::endl;
    std::cout << "\u001b[35;1m -> |" << "__Hex________:__Decimal___:__Char__" << std::endl;

    for ( int n = 0; n < 5; n++ ) {

        std::cout << "\u001b[35;1m -> |\u001b[0m";

        for ( int j = i; i < j+4; i++ ) {
            std::cout << " " << std::setfill('0') << std::setw(2) << std::hex << (int) message[i];
        }
        
        memcpy(&number, &message[i-4], 4);

        if ( number != std::numeric_limits<unsigned int>::max() && number != std::numeric_limits<unsigned int>::min() ) {

            printf(" : % 10u : ", number);

            if (n != 0)
                std::cout << "\u001b[35;1m";

            if ( n == 0 ) {
                std::cout << (char) message[i-4] << " ";
                std::cout << (char) message[i-3] << " ";
                std::cout << (char) message[i-2] << " ";
                std::cout << (char) message[i-1] << "\u001b[0m ";
            } else {
                std::cout << "        ";    
            }

        } else {
            std::cout << " :            :         ";
        }

        switch(n) {
            case 0: std::cout << "\u001b[30;1m// Packet description\u001b[0m"; break;
            case 1: std::cout << "\u001b[30;1m// Message data\u001b[0m"; break;
            case 2: std::cout << "\u001b[30;1m// Message data\u001b[0m"; break;
            case 3: std::cout << "\u001b[30;1m// Message data\u001b[0m"; break;
            case 4: std::cout << "\u001b[30;1m// Message data\u001b[0m"; break;
        }
        std::cout << std::endl;

    }
    
}

void print_hex_SP_received_followup(char* msg) {

    std::cout << "\u001b[35;1m -> |\u001b[0m" << std::endl;
    std::cout << "\u001b[35;1m -> |\u001b[0m" << " Decrypted text: \u001b[4m\u001b[35;1m"; printf("%s\u001b[0m\n", msg);

}

#endif