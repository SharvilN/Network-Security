
#include <bits/stdc++.h>
using namespace std;
#include <gmp.h>

int main(){

    string cipher_text = "XUKWLGEEYINNWBVLBWKUVXUCXLQYFJSHNHNVPRCWGQRPGMAASHTPVHIOTSJUIGJIJGFSQVFQQRMMAFIEIEEVIAEVLRXBVSBNWNUCBWWRGWRXIECPBHXUGQNTINXEVNEONINPHNTIDWMGGEONIGQTRTJBTQNHVRSYRPGLCRNNCFKWNPHGJYFVSRXIAIYRUWGJIFGGEGXXGCBHXUKWPKTUGVCNELKRTCVBWRQYMGJXUGQPCROGEYQXBHJHPFHVRBYTYGEFGJBTKRVEOQYGVLVUEAEMRPXFVYSHJBTXUGVRUXBHXUKWPQYEUIVPXUGVROEVPHRTSSVLRESHTWRYIJKPYHSPWWBPQBTIRNEOQVNVISQVZUSSUIPWVVVCGJEGEEAPSGDIOTSXGROAWHELNUMZRPRVIPJRVSYR";
//    cin >> cipher_text;
    int size = (unsigned)cipher_text.size();

    mpz_t frequency_of_factors[500];
    for(int i=0; i<500; i++){
        mpz_init(frequency_of_factors[i]);
    }

    for(int length = 3; length <=4; length++){
        for(int i=0; i<size - length + 1; i++){
            string pattern = cipher_text.substr(i, length);
            mpz_t pattern_indexes[500];
            for(int i=0; i<500; i++){
                mpz_init(pattern_indexes[i]);
            }

            int k=0;
            for(int j=0; j<size-length+1; j++){
                if(cipher_text.substr(j, length) == pattern){
                    mpz_t index;
                    mpz_init(index);
                    mpz_set_si(index, j);
                    mpz_set(pattern_indexes[k], index);
                    k++;
                }
            }
            int no_of_indexes = k;
            for(int index_i=0; index_i<no_of_indexes; index_i++){
                for(int index_j=index_i+1; index_j<no_of_indexes; index_j++){
                    mpz_t index_one, index_two;
                    mpz_init(index_one);
                    mpz_init(index_two);

                    mpz_set(index_one, pattern_indexes[index_i]);
                    mpz_set(index_two, pattern_indexes[index_j]);

                    mpz_t index_diff;
                    mpz_init(index_diff);
                    mpz_sub(index_diff, index_two, index_one);

                    mpz_t divisor;
                    mpz_init(divisor);
                    mpz_set_si(divisor, 2);
                    while(mpz_cmp(divisor, index_diff) != 0){
                        int is_divisible = mpz_divisible_p(index_diff, divisor);
                        if(is_divisible != 0){
                            mpz_add_ui(frequency_of_factors[mpz_get_si(divisor)], frequency_of_factors[mpz_get_si(divisor)], 1);
                        }
                        mpz_add_ui(divisor, divisor, 1);
                    }
                }
            }
        }
    }

    mpz_t key_length, max_frequency;
    mpz_init(key_length);
    mpz_init(max_frequency);
    for(int i=0; i< 500; i++){
        if(mpz_cmp(frequency_of_factors[i], max_frequency) > 0){
            mpz_set(max_frequency, frequency_of_factors[i]);
            mpz_set_si(key_length, i);
        }
    }
    gmp_printf("Key Length : %Zd\n", key_length);

    mpz_t frequency_attack[26];
    mpz_t key[mpz_get_ui(key_length)];

    for(int ind=0; ind<3; ind++){
        mpz_init(key[ind]);
    }

    for(int i=0; i<3; i++){
        for(int ind=0; ind<26; ind++){
            mpz_init(frequency_attack[ind]);
        }
        int row = i;
        while(row < size){
            mpz_t character;
            mpz_init(character);
            mpz_set_si(character, cipher_text[row] - 'A');
            int index_of_character = (int)mpz_get_si(character);
//            cout << " Index of character : " << index_of_character << endl;
            mpz_add_ui(frequency_attack[index_of_character], frequency_attack[index_of_character], 1);
            row += mpz_get_si(key_length);
        }

        mpz_t key_element, max_frequency_of_element;
        mpz_init(key_element);
        mpz_init(max_frequency_of_element);
        for(int index=0; index< 26; index++){
            if(mpz_cmp(frequency_attack[index], max_frequency_of_element) > 0){
                mpz_set(max_frequency_of_element, frequency_attack[index]);
                mpz_set_si(key_element, index);
            }
        }

        mpz_t diff;
        mpz_init(diff);
        mpz_set_si(diff, mpz_get_si(key_element) - 'E' + 65);

        if(mpz_get_si(diff) < 0){
            mpz_add_ui(diff, diff, 26);
        }
        mpz_set(key[i], diff);
    }

    string key_string = "";
    cout << "Key : ";
    for(int i=0; i<3; i++){

        gmp_printf("%Zd ", key[i]);
        key_string += mpz_get_si(key[i]) + 65;
    }
    cout << "Key String : " <<  key_string << endl;

    string plain_text = "";
    int ct=0;
    for(int i=0; i<cipher_text.size(); i++){
        if(cipher_text[i] - key_string[i%3] < 0){
            plain_text += cipher_text[i] - key_string[i%3] + 65 + 26;

//            cout << "char : " << cipher_text[i] - key_string[i%3] + 65 +26 << " ";

        }
        else {
//            cout << "char : " << cipher_text[i] - key_string[i%3] + 65<< " ";
            plain_text += cipher_text[i] - key_string[i % 3] + 65;
        }
        ct++;
    }
    cout << "Cipher Text : " << cipher_text << endl;
    cout << endl;
    cout << "Plain Text : " << plain_text << endl;
}