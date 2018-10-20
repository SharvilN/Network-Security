//
// Created by sharvil on 12/10/18.
//

#include <bits/stdc++.h>
using namespace std;

int main(){

    long p;
    cin >> p;

    set <long> qr;
    set <long> qnr;

    for(long i = 1 ; i < p; i++){
        qr.insert(i*i % p);
    }
    for(long i = 1 ; i < p ; i++){
        if(qr.count(i) == 0){
            qnr.insert(i);
        }
    }
    cout << "QR  : ";
    for(auto q:qr){
        cout << q << " ";
    }
    cout << endl;
    cout << "QNR : ";
    for(auto q:qnr){
        cout << q << " ";
    }
}