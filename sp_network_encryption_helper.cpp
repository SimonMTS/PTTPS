#ifndef sp_network_encryption_helper_H
#define sp_network_encryption_helper_H

class sp_network_encryption_helper {

    public:
    static void apply_sp_network_pass(char* msg, unsigned int key) {

        for ( int i = 0; i < 16; i++ ) {
            msg[i] = msg[i] ^ 0xff;
        }

    }
  
};

#endif