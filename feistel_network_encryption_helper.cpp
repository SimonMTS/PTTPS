#ifndef feistel_network_encryption_helper_H
#define feistel_network_encryption_helper_H

#include <bits/stdc++.h>

class feistel_network_encryption_helper {

    public:
    const static int number_of_feistel_rounds = 10;

    static void apply_feistel_network_pass(unsigned char* msg, unsigned int* key_array) {

        unsigned char feistel_left[8];
        memcpy(&feistel_left[0], &msg[0], 8);

        unsigned char feistel_right[8];
        memcpy(&feistel_right[0], &msg[8], 8);

        for ( int n = 0; n < number_of_feistel_rounds; n++ ) {

            unsigned char tmp_feistel_left[8];
            unsigned char tmp_feistel_right[8];
            unsigned char F_feistel[8];

            memcpy(&tmp_feistel_left[0], &feistel_right[0], 8);

            memcpy(&F_feistel[0], &feistel_right[8], 8);
            feistel_f(&F_feistel[0], key_array[n]);

            for ( int i = 0; i < 16; i++ ) {
                tmp_feistel_right[i] = F_feistel[i] ^ tmp_feistel_left[i];
            }

            memcpy(&feistel_left[0], &tmp_feistel_left[0], 8);
            memcpy(&feistel_right[0], &tmp_feistel_right[0], 8);

        }

        memcpy(&msg[0], &feistel_right[0], 8);
        memcpy(&msg[8], &feistel_left[0], 8);

    }

    private:
    static void feistel_f(unsigned char* msg, unsigned int r) {

        ///
        for ( int i = 0; i < 8; i++ ) {
            // msg[i] = msg[i] + 1;
        }
        return;
        ///


        srand(r);

        for ( int i = 0; i < 8; i++ ) {
            msg[i] = s_box(msg[i], rand());
        }

        p_box(msg, rand());

    }

    static char s_box(unsigned char c, unsigned int r) {

        return c ^ r;

    }

    static void p_box(unsigned char* c, unsigned int r) {

        srand(r);
        char old[16];
        memcpy(&old, c, 16);

        int positions[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

        for ( int i = 0; i < 16; i++ ) {

            // pick pseudorandom position
            int r = rand();
            int pos_pos = i == 15 ? 0 : r % (15 - i);
            int pos = positions[pos_pos];
            std::swap(positions[pos_pos], positions[(15 - i)]);

            // apply permutation
            c[i] = old[pos];
        }

    }
  
};

#endif