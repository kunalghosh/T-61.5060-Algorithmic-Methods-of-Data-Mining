/*
 * =====================================================================================
 *
 *       Filename:  get_hashes.cpp
 *
 *    Description:  Reads in a string from STDIN and prints out its hash
 *
 *
 *        Version:  1.0
 *        Created:  12/30/2015 21:56:36
 *       Revision:  none
 *       Compiler:  clang c++11
 *
 *         Author:  Kunal Ghosh, 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <cstdlib>
#include <string>
#include <iostream>
#include <bitset>
#include "../hashes.h"

int main(int argc, char *argv[]){
    
    std::string hashFunc = "poly";
    unsigned int bit_limit = 0;
    if(argc == 2){
        hashFunc = argv[1];
    } else if (argc == 3){
        hashFunc = argv[1];
        bit_limit = std::stoi(argv[2]);
    } else {
        std::cerr << "Please put in the name of the hash function to display (using poly by default). \nPossible Options :\n";
        for(auto v: algos){
            std::cerr << v.first << std::endl;
        }

    }
    std::ios::sync_with_stdio(false);
    std::string a;

    while(getline(std::cin, a)){
        if(a.empty()){
            a = '\n';
        }
        // std::cerr << "Bit str : " << std::bitset<90>(hashstr(hashFunc, a, bit_limit))  << std::endl;
        std::cout << hashstr(hashFunc, a, bit_limit) << std::endl;
    }
    return 0;
}

