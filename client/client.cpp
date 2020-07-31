#include <client/pttps_base_client.cpp>
#include <client/pttps_key_exchange_client.cpp>

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        printf("\nPlease specify an ip address and a message \n");
        return -1;
    }

    pttps_key_exchange_client key_exchange_client( strdup(argv[1]) );

    unsigned int k = key_exchange_client.generate_key();

    printf("Shared_key: %llu\n", k);

    return 0;
}