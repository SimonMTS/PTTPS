#include <functional>
#include <server/pttps_base_server.cpp>
#include <diffie_hellmann_helper.cpp>
#include <feistel_network_encryption_helper.cpp>
#include <hex_helper.cpp>
#include <map>

void callback(unsigned char* received_message, unsigned int socket_uid);

pttps_base_server pttps_server;
int main(int argc, char const *argv[]) 
{

    pttps_server.port = 8080;
    pttps_server.setup();

    pttps_server.listener_setup( callback );

    return 0;
}


std::map<unsigned int, unsigned int> shared_keys;

void on_dh_msg(unsigned char* rm, unsigned int uid);
void on_encrypted_msg(unsigned char* rm, unsigned int uid);

void callback(unsigned char* received_message, unsigned int socket_uid)
{
    
    char type[5] = { '\0', '\0', '\0', '\0', '\0' };
    memcpy(&type[0], &received_message[0], 4);
    
    if ( strcmp(type, "DHKE") == 0 ) {
        on_dh_msg( received_message, socket_uid );
    } else if ( strcmp(type, "ENCR") == 0 ) {
        on_encrypted_msg( received_message, socket_uid );
    } else if ( strcmp(type, "STOP") == 0 ) {
        exit(EXIT_SUCCESS);
    }

}

void on_dh_msg(unsigned char* received_message, unsigned int socket_uid)
{

    print_hex_DH_received(received_message);


    unsigned int k;
    unsigned int list[5] = { 0, 0, 0, 0, 0 };
    {
        {
            memcpy(&list[0], &received_message[ 4], 4);
            memcpy(&list[1], &received_message[ 8], 4);
            memcpy(&list[3], &received_message[12], 4);
        }

        diffie_hellmann_helper DHH;
        DHH.generate_response_variables(list);

        memcpy(&received_message[16], &list[4], 4);

        k = DHH.calc_shared_key(list, list[3]);

        shared_keys[socket_uid] = k;
    }
    
    pttps_server.send_msg(received_message);


    print_hex_DH_received_followup(list[2], list[4], k);

    print_hex_DH_sent(received_message);

}

void on_encrypted_msg(unsigned char* received_message, unsigned int socket_uid)
{

    print_hex_encrypted_received(received_message);


    unsigned char msg[17];
    memcpy(&msg[0], &received_message[4], 16);
    msg[16] = '\0';

    srand(shared_keys[socket_uid]);
    unsigned int key_array[feistel_network_encryption_helper::number_of_feistel_rounds];
    for ( int i = feistel_network_encryption_helper::number_of_feistel_rounds-1; i >= 0; i-- ) {
        key_array[i] = rand();
    }

    feistel_network_encryption_helper::apply_feistel_network_pass(msg, key_array);
    memcpy(&received_message[4], &msg[0], 16);

    print_hex_plaintext_msg(received_message);

    print_hex_encrypted_received_followup(msg);
    
}