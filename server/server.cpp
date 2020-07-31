#include <functional>
#include <server/pttps_base_server.cpp>
#include <diffie_hellmann_helper.cpp>
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

void callback(unsigned char* received_message)
{

    std::cout << "\nReceived msg:\n"; 
    print_hex(received_message);


    // bad
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


    std::cout << "\n\nSent msg:\n"; 
    print_hex(received_message);
    std::cout << "\n\n";

    printf("\nPrivate_key: %llu\n", list[2]);
    printf("Shared_key: %llu\n\n-\n", k);

}