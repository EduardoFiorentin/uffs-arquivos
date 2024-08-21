// #include <bits/stdc++.h>
#include <iostream> 
#include <stdlib.h>
#include <vector>

#define ll int

using namespace std;

vector<ll> memo;

int solve(ll i, ll c, ll n, vector<ll> peso, vector<ll> valor){

    if(i > n || c == 0){
        return 0;
    }

    if(memo[c]) return memo[c];

    if(peso[i] > c){
        return solve(i+1, c, n, peso, valor);
    }

    ll adc = valor[i] + solve(i+1, c-peso[i], n, peso, valor);
    ll nadc = solve(i+1, c, n, peso, valor);

    return memo[c] = max(adc, nadc);
}

int main(){
    ll n, c;
    cin >> n >> c;

    vector<ll> peso(n);
    vector<ll> valor(n);
    memo.resize(c + 1, 0);

    for(int i=0; i<n; i++){
        cin >> valor[i];
        cin >> peso[i];
    }

    ll res = solve(1, c, n, peso, valor);

    cout << res << "\n";

    return 0;
}