#include <functional>
#include <server/pttps_base_server.cpp>
#include <diffie_hellmann_helper.cpp>
#include <sp_network_encryption_helper.cpp>
#include <hex_helper.cpp>

void callback(unsigned char* received_message);

pttps_base_server pttps_server;
int main(int argc, char const *argv[]) 
{

    pttps_server.port = 8080;
    pttps_server.setup();

    pttps_server.listener_setup( callback );

    return 0;
}

void on_dh_msg(unsigned char* rm);
void on_sp_msg(unsigned char* rm);

void callback(unsigned char* received_message)
{
    
    char type[5] = { '\0', '\0', '\0', '\0', '\0' };
    memcpy(&type[0], &received_message[0], 4);
    
    if ( strcmp(type, "DHKE") == 0 ) {
        on_dh_msg( received_message );
    } else if ( strcmp(type, "SPNE") == 0 ) {
        on_sp_msg( received_message );
    }

}

void on_dh_msg(unsigned char* received_message)
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
    }
    
    pttps_server.send_msg(received_message);


    print_hex_DH_received_followup(list[2], list[4], k);

    print_hex_DH_sent(received_message);

}

void on_sp_msg(unsigned char* received_message)
{

    print_hex_SP_received(received_message);


    char msg[17];
    memcpy(&msg[0], &received_message[4], 16);
    msg[16] = '\0';

    sp_network_encryption_helper::apply_sp_network_pass(msg, 0);

    print_hex_SP_received_followup(msg);
    
}