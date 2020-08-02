#include <client/pttps_base_client.cpp>
#include <client/pttps_key_exchange_client.cpp>
#include <client/pttps_encrypted_msg_client.cpp>
#include <cstring>

int main(int argc, char const **argv)
{
    if (argc < 3) {
        printf("\nclient [ip address] [message ...] \n");
        printf("\nPlease specify an ip address and a message. \n");
        return -1;
    }

    std::vector<char> input_string;
    for ( int i = 2; i < argc; i++ ) {
        char* msg_chunk = strdup(argv[i]);
        for ( int j = 0; j < strlen(msg_chunk); j++ ) {

            input_string.push_back( msg_chunk[j] );

        }
        input_string.push_back(' ');
    }

    char input[input_string.size()-1];
    std::copy(input_string.begin(), input_string.end()-1, input);
    input[input_string.size()-1] = '\0';
    

    pttps_base_client base_client(strdup(argv[1]), 8080);


    if ( strcmp(input, "stop") == 0 ) {
        base_client.send_stop_msg();
        std::cout << std::endl;
        return 0;
    }


    pttps_key_exchange_client key_exchange_client( &base_client );

    unsigned int k = key_exchange_client.generate_key();

    pttps_encrypted_msg_client encrypted_msg_client( &base_client, k );

    encrypted_msg_client.send_msg( input, input_string.size()-1 );

    std::cout << std::endl;
    return 0;
}