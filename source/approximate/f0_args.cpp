/*
 * =====================================================================================
 *
 *       Filename:  f0.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/25/2015 17:00:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <unordered_map>
#include <functional>
#include <cstring>
#include <bitset>
#include <random>
#include <map>
#include "hashes.h"

#define endl "\n"
using namespace std;

// unsigned long long hashstr(string algo, string str, unsigned long long seed1, unsigned long long seed2){
//     map<string,int> algos = {{"jenkins",1},{"paul",2},{"cpp",3},{"mm2",4},{"poly",5},{"mm64a",6},{"rsh",7}};
//     switch(algos[algo]){
//         case 1:
//             return jenkins_one_at_a_time_hash(str);
//             break;
//         case 2:
//             return paul_hash(str, seed1);
//             break;
//         case 3:
//             return hash<string>()(str);
//             break;
//         case 4:
//             return MurmurHash2(str, (int) strlen(str.c_str()), seed1);
//             break;
//         case 5:
//             return polynomial_hash(str,seed1);
//             break;
//         case 6:
//             return MurmurHash64A(&str, (int) strlen(str.c_str()), seed1);
//             break;
//         case 7:
//             return RSHash(str,seed1,seed2);
//             break;
//         default:
//             cerr << "Undefined hashing algorithm." << endl;
//             break;
//     }
//     return -1;
// }

unsigned long long rho(unsigned long hashVal){
    unsigned long long rho = 0;
    int mask = 0x1;
    if(hashVal != 0){
        while((hashVal & mask) == 0){
            rho++;
            hashVal = hashVal  >> 1;
            // cout << hashVal << endl;
        }
    }
    return rho; 
}

void set_bit(unsigned long long &bit_str, long long pos){
    long long mask = 0x1 << pos; // because pos i.e. rho also starts from 0
    bit_str = bit_str | mask; 
}

// unsigned long long get_estimated_distinct_nums(unsigned long long bit_str){
//     double phi = 0.77351;
//     unsigned long long pos = 0;
//     while(bit_str != 0){
//         bit_str = bit_str >> 1;
//         pos++;
//     }
//     // return (pow(2,pos) / phi) ;
//     return (pow(2,pos)) ;
// }

unsigned long long get_estimated_distinct_nums(unsigned long long bit_str){
    // Implementing the leftmost zero
    double phi = 0.77351;
    unsigned long long pos = 0;
    int mask = 0x1;
    // cerr << "Bit str : " << bitset<24>(bit_str)  << endl;   
    while((bit_str & mask)!= 0){
        bit_str = bit_str >> 1;
        pos++;
    }
    return (pow(2,pos) / phi) ;
}


int main(int argc, char *argv[]){
    // We are expecting three arguments, name of hash function to use and 2 prime numbers as seeds for our algorithms.
    // Otherwise we expect no arguments and initialize the hash function to polynomial hash and two default prime seems
    // which are arbitrary prime numbers.
    // You can choose to pass in just the hashFunction name too, in which case the default prime seeds are used.
    // But you cannot change the prime seeds without specifying a hash function name
    unsigned long long arg1 = 363019, arg2 = 50591; 
    string hashFunc = "poly";
    unsigned int bit_limit = 0;

    if(argc == 4){
        hashFunc = argv[1];
        arg1 = strtoll(argv[2],NULL,10);
        arg2 = strtoll(argv[3],NULL,10);    
    } else if(argc == 5){
        hashFunc = argv[1];
        bit_limit = stoi(argv[2]);
        arg1 = strtoll(argv[3],NULL,10);
        arg2 = strtoll(argv[4],NULL,10);    
    } else if (argc == 3){
        hashFunc = argv[1];
        bit_limit = stoi(argv[2]);
    } else if (argc == 2){
        hashFunc = argv[1];
    } else {
        cerr << "Invalid Number of arguments.\nPlease pass a hash function name 'and' 0 or 2 prime numbers as an argument.\nUsing defaults"
             << " hash func = "
             << hashFunc
             << " arg1 = "
             << arg1 
             << " arg2 = "
             << arg2 
             << endl;
    }
    string a;
    ios::sync_with_stdio(false);
    unsigned long long bit_fields = 0;
    while(getline(cin,a)){
        if(a.empty()){
            a = "\n";
        }
        // cout << a << " -- " << hashstr(a) << endl;
        // std::cerr << "Bit str : " << std::bitset<90>(hashstr(hashFunc, a, bit_limit,arg1,arg2))  << endl;
        set_bit(bit_fields, int(rho(hashstr(hashFunc,a,bit_limit,arg1,arg2))));  
       //  cout << hashstr(a) << " " << rho(hashstr(a)) << endl;
    }
    cout << get_estimated_distinct_nums(bit_fields) << endl;
    return 0;
}
