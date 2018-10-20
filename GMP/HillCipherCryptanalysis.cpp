//
// Created by sharvil on 9/9/18.
//

#include <iostream>
#include <gmp.h>
using namespace std;

bool mat_inverse(mpz_t[][2]);
void inverse(mpz_t[], mpz_t[], mpz_t[], mpz_t[]);
mpz_t** mat_multiply(mpz_t[][2], mpz_t[][2]);
void mat_mod(mpz_t**, int);

int main(){
    string ctext, ptext;
    int i;
    cout << "Enter cypher text: ";
    cin >> ctext;
    cout << "Enter plain text: ";
    cin >> ptext;
    if(!(ctext.size() > 3 && ptext.size() > 3))
        cout << "Key cannot be found out!";
    else{
        mpz_t p[2][2], c[2][2];
        for(i = 0; i < 4; i++) {
            mpz_init(p[i / 2][i % 2]);
            mpz_init(c[i / 2][i % 2]);
        }
        for(i = 0; i < 4; i++){
            mpz_set_si(p[i / 2][i % 2], ptext[i] - 64);
            mpz_set_si(c[i / 2][i % 2], ctext[i] - 64);
        }
        bool done = mat_inverse(p);
        if(done){
            mpz_t** key = mat_multiply(p, c);
            mat_mod(key, 26);
            cout << "Key is:    ";
            for(i = 0; i < 4; i++){
                mpz_out_str(stdout, 10, key[i / 2][i % 2]);
                cout << "\t";
            }
            cout << "\n";
        }
        else {
            cout << "Inverse of plain text could not be found as determinant does not belong to Z26*."
                    " Hence key cannot be found.\n";
        }
    }
    return 0;
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

mpz_t** mat_multiply(mpz_t a[][2], mpz_t b[][2]){
    mpz_t temp, temp2;
    mpz_init(temp);
    mpz_init(temp2);
    mpz_t** res = (mpz_t**) malloc(sizeof(mpz_t*) * 2);
    int i, j, k;
    for(i = 0 ; i < 2; i++)
        res[i] = (mpz_t*) malloc(sizeof(mpz_t) * 2);
    for(i = 0; i < 2; i++){
        for(j = 0; j < 2; j++){
            mpz_init(res[i][j]);
            mpz_set_si(temp, 0);
            for(k = 0; k < 2; k++){
                mpz_mul(temp2, a[i][k], b[k][j]);
                mpz_add(temp, temp, temp2);
            }
            mpz_set(res[i][j], temp);
        }
    }
    return res;
}

void mat_mod(mpz_t** mat, int k){
    for(int i = 0; i < 4; i++){
        mpz_mod_ui(mat[i / 2][i % 2], mat[i / 2][i % 2], k);
    }
}