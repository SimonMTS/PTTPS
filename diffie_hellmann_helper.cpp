#ifndef diffie_hellmann_helper_H
#define diffie_hellmann_helper_H

#include <random>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <gmp.h>

class diffie_hellmann_helper {

    private:
    std::vector<char> primes_array;
    size_t primes_array_length = 0;


    public:
    diffie_hellmann_helper() {
        
        std::ifstream infile("./primes.32b");
        
        infile.seekg(0, std::ios::end);
        this->primes_array_length = infile.tellg();
        infile.seekg(0, std::ios::beg);
        
        this->primes_array.resize(this->primes_array_length);    
        
        infile.read(&this->primes_array[0], this->primes_array_length);
        infile.close();

    }

    void generate_request_variables(unsigned int* list) {

        std::random_device rd;
        std::mt19937_64 e2(rd());
        std::uniform_int_distribution<unsigned int> dist(0, std::numeric_limits<unsigned int>::max());

        /* n */ list[0] = this->random_prime( std::numeric_limits<unsigned int>::max() );
        /* g */ list[1] = this->random_prime( list[0] );
        /* x */ list[2] = dist(e2);
        /* a */ list[3] = this->pow_and_mod( list[1], list[2], list[0] );

    }

    void generate_response_variables(unsigned int* list) {

        std::random_device rd;
        std::mt19937_64 e2(rd());
        std::uniform_int_distribution<unsigned int> dist(0, std::numeric_limits<unsigned int>::max());

        /* y */ list[2] = dist(e2);
        /* b */ list[4] = this->pow_and_mod( list[1], list[2], list[0] );

    }

    unsigned int calc_shared_key(unsigned int* list, unsigned int swapped_value) {

        return this->pow_and_mod( swapped_value, list[2], list[0] );

    }


    private:
    unsigned int random_prime(unsigned int max) {

        unsigned int prime;
        while (true) {

            int pre_calc_primes_size = 203280220;

            std::random_device rd;
            std::mt19937_64 e2(rd());
            std::uniform_int_distribution<unsigned int> dist(0, pre_calc_primes_size);
            unsigned int rn = ((dist(e2) % pre_calc_primes_size) * 4);

            memcpy(&prime, &this->primes_array[rn], 4);

            if ( prime < max ) break;
        }

        return prime;

    }

    unsigned int pow_and_mod(unsigned int base, unsigned int expo, unsigned int mod) {

        int flag;

        mpz_t mpz_res;
        mpz_t mpz_base;
        mpz_t mpz_expo;
        mpz_t mpz_mod;

        mpz_init(mpz_res);
        mpz_init(mpz_base);
        mpz_init(mpz_expo);
        mpz_init(mpz_mod);
        
        mpz_set_ui(mpz_res,0);
        mpz_set_ui(mpz_base,base);
        mpz_set_ui(mpz_expo,expo);
        mpz_set_ui(mpz_mod,mod);

        mpz_powm_sec( mpz_res, mpz_base, mpz_expo, mpz_mod );

        unsigned int result = mpz_get_ui(mpz_res);

        mpz_clear(mpz_res);
        mpz_clear(mpz_base);
        mpz_clear(mpz_expo);
        mpz_clear(mpz_mod);
        

        return result;

    }
  
};

#endif