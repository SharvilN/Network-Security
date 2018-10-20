//
// Created by sharvil on 12/10/18.
//
#include <bits/stdc++.h>
using namespace std;
vector <int> primes;
const int N = 1001;
vector <int> sieve(N);

long power(long x, long y, long p)
{
    long res = 1;
    x = x % p;
    while (y > 0)
    {
        if (y & 1) {
            res = (res * x) % p;
        }
        y = y>>1;
        x = (x*x) % p;
    }
    return res;
}

void findPrimefactors(unordered_set<int> &s, int n){
    while (n%2 == 0){
        s.insert(2);
        n = n/2;
    }

    for (int i = 3; i <= sqrt(n); i = i+2){
        while (n%i == 0){
            s.insert(i);
            n = n/i;
        }
    }

    if (n > 2)
        s.insert(n);
}

void findPrimitive(set<int>& ret, int n){
    unordered_set<int> s;

    if (sieve[n]!= 1){
        int phi = n-1;
        findPrimefactors(s, phi);

        for (int r=2; r<=phi; r++){
            bool flag = false;
            for (auto it = s.begin(); it != s.end(); it++){

                if (power(r, phi/(*it), n) == 1){
                    flag = true;
                    break;
                }
            }

            if (flag == false)
            ret.insert(r);
        }
    }

}

int main(){
    srand(time(NULL));
    for(int i = 2 ; i < N; i++ ){
        if(sieve[i] == 0){
            primes.push_back(i);
            for(int j = 2*i ; j < N; j+= i){
                sieve[j] = 1;
            }
        }
    }

    long p;
    cin >> p;
    cout << "The primitive roots : ";
    set <int> primitve_roots;
    findPrimitive(primitve_roots, p);

    for(auto p:primitve_roots){
        cout << p << " ";
    }
    cout << endl;
}
