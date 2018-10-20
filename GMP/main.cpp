#include <bits/stdc++.h>
using namespace std;
#include <gmp.h>

void gcd(mpz_t &g, mpz_t &s, mpz_t &t, mpz_t a, mpz_t b);
void invert(mpz_t &rinv, mpz_t a, mpz_t b);

// Implementation of the Extended Euclidean algorithm
// for computing greatest common divisor and inversion
void gcd(mpz_t &g, mpz_t &s, mpz_t &t, mpz_t a, mpz_t b)
{
    mpz_t r0, r1;
    mpz_init(r0);
    mpz_init(r1);
    mpz_set(r0, b);
    mpz_set(r1, a);

    mpz_t s0, s1;
    mpz_init(s0);
    mpz_init(s1);
    mpz_set_si(s0, 0);
    mpz_set_si(s1, 1);

    mpz_t t0, t1;
    mpz_init(t0);
    mpz_init(t1);
    mpz_set_si(t0, 1);
    mpz_set_si(t1, 0);

    mpz_t q;
    mpz_init(q);

    while (mpz_cmp_si(r0, 0) != 0) {
        mpz_div(q, r1, r0);

        mpz_t rtmp, stmp, ttmp;
        mpz_init(rtmp);
        mpz_init(stmp);
        mpz_init(ttmp);

        mpz_mul(rtmp, q, r0);
        mpz_mul(stmp, q, s0);
        mpz_mul(ttmp, q, t0);

        mpz_swap(r0, r1);
        mpz_sub(r0, r0, rtmp);

        mpz_swap(s0, s1);
        mpz_sub(s0, s0, stmp);

        mpz_swap(t0, t1);
        mpz_sub(t0, t0, ttmp);

        mpz_clear(rtmp);
        mpz_clear(stmp);
        mpz_clear(ttmp);
    }

    mpz_init(g);
    mpz_abs(r1, r1);
    mpz_set(g, r1);

    mpz_init(s);
    mpz_set(s, s1);

    mpz_init(t);
    mpz_set(t, t1);

    mpz_clear(r0);
    mpz_clear(r1);
    mpz_clear(s0);
    mpz_clear(s1);
    mpz_clear(t0);
    mpz_clear(t1);
    mpz_clear(q);
}

// Implementation of multiplicative inverse
// using the Extended Euclidean algorithm
void invert(mpz_t &rinv, mpz_t a, mpz_t b)
{
    mpz_t g, s, t;
    mpz_init(g);
    mpz_init(s);
    mpz_init(t);

    // compute coefficients
    gcd(g, s, t, a, b);

    if (mpz_cmp_si(s, 0) < 0) {
        mpz_add(s, s, b);
    }

    mpz_init(rinv);
    mpz_set(rinv, s);

    mpz_clear(g);
    mpz_clear(s);
    mpz_clear(t);
}

int main(){
    int given_a, given_b;
    cin >> given_a >> given_b;
    mpz_t rinv, a, b;
    mpz_init(rinv);
    mpz_init(a);
    mpz_init(b);
    mpz_set_si(a, given_a);
    mpz_set_si(b, given_b);
    invert(rinv, a, b);
    gmp_printf("%Zd", rinv);

    // Encryption
    mpz_t given_key;
    char* key_string;
    cin >> key_string;
    mpz_init_set_str(given_key, key_string, 10);

    int key_string_size = sqrt(strlen(given_key));
    mpz_t key_size;
    mpz_init(key_size);
    mpz_set_si(key_size, key_string_size);
    mpz_t key[]
}