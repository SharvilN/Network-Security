//
// Created by sharvil on 9/9/18.
//
#include <iostream>
#include <gmp.h>
using namespace std;

string encipher(string, mpz_t[][2]);
string decipher(string, mpz_t[][2]);
bool mat_inverse(mpz_t[][2]);
void inverse(mpz_t[], mpz_t[], mpz_t[], mpz_t[]);
mpz_t* multiply(mpz_t[], mpz_t[][2]);

int main() {
    string str, res;
    char inputStr[1024];
    mpz_t key[2][2];
    int i, dec_flag;
    cout << "Enter the string to be enciphered/deciphered:";
    cin >> str;
    cout << "Enter 0 to encipher or 1 to decipher:";
    cin >> dec_flag;
    cout << "Enter elements of key:";
    for(i = 0; i < 4; i++){
        int flag = 1;
        scanf("%s", inputStr);
        mpz_init(key[i / 2][i % 2]);
        mpz_set_si(key[i / 2][i % 2], 0);
        flag = mpz_set_str(key[i / 2][i % 2], inputStr, 10);
        if(flag != 0){
            cout << "Something went wrong while assigning";
        }
    }
    if(dec_flag) {
        res = decipher(str, key);
        if(res.compare("") != 0)
            cout << "Deciphered text: " << res;
    }
    else {
        res = encipher(str, key);
        cout << "Enciphered text: " << res;
    }
    printf ("\n");

    return 0;
}

string encipher(string s, mpz_t key[][2]){
    string dec;
    int size = s.size();
    mpz_t temp[2];
    mpz_init(temp[0]);
    mpz_init(temp[1]);
    int i, k;
    k = (size / 2) + (size % 2);
    for(i = 0; i < k; i++){
        mpz_set_si(temp[0], s[2 * i] - 65);
        if((2 * i + 1) < size) {
            mpz_set_si(temp[1], s[2 * i + 1] - 65);
        }
        else
            mpz_set_si(temp[1], 23);
        mpz_t* res = multiply(temp, key);
        dec.push_back((char)(mpz_get_si(res[0]) + 65));
        dec.push_back((char)(mpz_get_si(res[1]) + 65));
    }
    return dec;
}


string decipher(string s, mpz_t key[][2]){
    bool done = mat_inverse(key);
    if(done)
        return encipher(s, key);
    else {
        cout << "Inverse of key could not be found as determinant does not belong to Z26*";
        return "";
    }
}


bool mat_inverse(mpz_t key[][2]){
    mpz_t det, temp, temp2, temp3;
    mpz_init(det);
    mpz_init(temp);
    mpz_init(temp2);
    mpz_init(temp3);
    mpz_mul(det, key[0][0], key[1][1]);
    mpz_mul(temp, key[0][1], key[1][0]);
    mpz_sub(det, det, temp);
    if(mpz_cmp_si(det, 0) == 0) {
        return false;
    }
    else{
        mpz_set_si(temp, 0);
        mpz_set_si(temp2, 1);
        mpz_set_si(temp3, 26);
        while(mpz_cmp_si(det, 0) < 0)
            mpz_add_ui(det, det, 26);
        inverse(&temp3, &det, &temp, &temp2);
        if(mpz_cmp_si(temp3, 1) == 0){
            mpz_set(temp3, key[0][0]);
            mpz_set(key[0][0], key[1][1]);
            mpz_set(key[1][1], temp3);
            mpz_neg(key[0][1], key[0][1]);
            mpz_neg(key[1][0], key[1][0]);
            mpz_mul(key[0][0], key[0][0], temp);
            mpz_mul(key[0][1], key[0][1], temp);
            mpz_mul(key[1][0], key[1][0], temp);
            mpz_mul(key[1][1], key[1][1], temp);
            mpz_mod_ui(key[0][0], key[0][0], 26);
            mpz_mod_ui(key[0][1], key[0][1], 26);
            mpz_mod_ui(key[1][0], key[1][0], 26);
            mpz_mod_ui(key[1][1], key[1][1], 26);
            return true;
        } else
            return false;
    }
}


void inverse(mpz_t r1[], mpz_t r2[],mpz_t t1[], mpz_t t2[]){
    if(mpz_cmp_si(r2[0], 0) != 0) {
        mpz_t q, r, t, temp1;
        mpz_init(q);
        mpz_init(r);
        mpz_init(t);
        mpz_init(temp1);
        mpz_fdiv_q(q, r1[0], r2[0]);
        mpz_fdiv_r(r, r1[0], r2[0]);
        mpz_mul(temp1, q, t2[0]);
        mpz_sub(t, t1[0], temp1);
        mpz_set(r1[0], r2[0]);
        mpz_set(r2[0], r);
        mpz_set(t1[0], t2[0]);
        mpz_set(t2[0], t);
        inverse(r1, r2, t1, t2);
    }
}


mpz_t* multiply(mpz_t str[], mpz_t key[][2]){
    mpz_t temp1, temp2;
    mpz_t* res = nullptr;
    res = (mpz_t*) malloc(sizeof(mpz_t) * 2);
    mpz_init(temp1);
    mpz_init(temp2);
    mpz_init(res[0]);
    mpz_init(res[1]);
    int i;
    for(i = 0; i < 2; i++){
        mpz_mul(temp1, str[0], key[0][i]);
        mpz_mul(temp2, str[1], key[1][i]);
        mpz_add(temp1, temp1, temp2);
        mpz_set_si(temp2, 26);
        mpz_mod(res[i], temp1, temp2);
    }
    return res;
}
