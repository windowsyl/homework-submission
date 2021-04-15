#include <stdio.h>
#include <gmp.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void fibToLen(mpz_t n, unsigned int len) {
    //for normal fib numbers, assume n is init to 0
    mpz_t m;
    mpz_init_set_d(m, 1);
    
    //get close to the right num
    do {
        mpz_add(n, n, m);
        mpz_add(m, n, m);
    } while (mpz_sizeinbase(m, 10) < len);
    
    //check if you overshot b/c counting by 2
    char *nstr;
    gmp_asprintf(&nstr, "%Zd", n);
    
    //check if you can trust sizeinbase
    char *mstr;
    gmp_asprintf(&mstr, "%Zd", m);

    if(strlen(nstr) < len && strlen(mstr) >= len) {
        //if everything lucked out, set m, the correct value, to n, the outparameter
        mpz_set(n, m);
    } else if(strlen(mstr) < len) {
        mpz_add(n, n, m);
    }
    //else nster >= len, which means it's ready to be used

    mpz_clear(m);
    free(nstr);
    free(mstr);
}

int main( int argc, char *argv[] ) {
    mpz_t n;
    mpz_init_set_d(n, 0);

    fibToLen(n, 1000);

    gmp_printf("%Zd", n);
    mpz_clear(n);
    return 0;
}
