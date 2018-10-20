//
// Created by sharvil on 12/10/18.
//
#include <bits/stdc++.h>
using namespace std;

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

void find_m_and_k(long n, long& m, long& k) {
    bool found = false;
    k = 0;
    while(!found){
        m = (n-1)/(long)pow(2, k);
        long rem =(n-1)%(long)pow(2, k);
        if(m%2 != 0 && rem == 0) {
            found = true;
            cout << "m : " << m << " k : " << k << endl;
        }
        else{
            k++;
        }
    }
}

bool miller_rabin_test(long n, long a) {
    long m, k;
    find_m_and_k(n, m, k);
    cout << "a : " << a << endl;
    long t = power(a, m, n);
    cout << "t : " << t << endl;

    if(t == 1 || t-n == -1){
        return true;
    }
    else{
        for(long i=1; i<k; i++){
            t = (t*t)%n;
            cout << "t : " << t << endl;
            if(t == 1){
                return false;
            }
            else if(t-n == -1){
                return true;
            }
        }
    }
    return false;
}

int main(){
    long n, a;
    cout << "Enter n : ";
    cin >> n;
    cout << "Want 'a' to be randomly generated? (yes or no) : ";
    string yes_or_no;
    cin >> yes_or_no;
    if(yes_or_no == "no"){
        cout << "Enter a : ";
        cin >> a;
        bool is_prime = miller_rabin_test(n, a);
        if(is_prime){
            cout << n << " is a prime number" << endl;
        }
        else{
            cout << n << " is a composite number" << endl;
        }
    }
    else{
        cout << "Enter number of random witnesses(a's) : ";
        int s;
        cin >> s;
        srand(time(0));
        bool failed = false;
        for(int i = 0; i<s && !failed; i++) {
            a = rand()%n;
            bool is_prime = miller_rabin_test(n, a);
            if(!is_prime){
                failed = true;
            }
        }
        if(!failed){
            cout << n << " is a prime number" << endl;
        }
        else{
            cout << n << " is a composite number" << endl;
        }
    }
}