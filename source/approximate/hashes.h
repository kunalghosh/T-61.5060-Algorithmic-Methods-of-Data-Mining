#ifndef HASHES_H
#define HASHES_H
/*
 * =====================================================================================
 *
 *       Filename:  hashes.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/26/2015 20:15:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <cstdlib>
#include <cmath>
#include <unordered_map>
#include <functional>
#include <cstring>
#include <iostream>
#include <map>

extern std::map<std::string,int> algos;
unsigned long long hashstr(std::string algo, std::string str, unsigned int bit_limit = 0, unsigned long long seed1 = 363019, unsigned long long seed2 = 363277);
unsigned long long polynomial_hash(std::string str, unsigned long seed = 5381);
unsigned long long djb2(std::string str, unsigned long seed = 5381);
unsigned long long jenkins_one_at_a_time_hash(std::string key);
unsigned long long paul_hash(std::string str,unsigned int seed = 5381);
uint32_t MurmurHash2 ( std::string key, int len, uint32_t seed = 5381 );
uint64_t MurmurHash64A ( const void * key, int len, uint64_t seed = 5381);
unsigned long long RSHash(const std::string str, unsigned long long a = 5381, unsigned long long b = 2887);
unsigned long long sum_mod(std::string str, unsigned long long seed = 5381);

#endif /*  HASHES_H */
