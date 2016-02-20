/*
 * =====================================================================================
 *
 *       Filename:  f2_newv2_1.cpp
 *
 *    Description:  Implementation of the simple F2 algorithm in C++
 *
 *        Version:  1.0
 *        Created:  12/31/2015 06:32:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <random>
#include <algorithm>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]){
    string outputFile = "f2_values_cpp.txt";
    // unsigned long long S = 4100000;
    unsigned long long S = 200;
    char *end;
    if(argc == 2){
        outputFile = argv[1];
        // S = strtoull(argv[1], &end,10);
    }
    if(argc == 3){
        outputFile = argv[1];
        S = strtoull(argv[2], &end,10);
    }
    
    unsigned long long idx_to_del;
    string line_to_del;

    map<string, vector<unsigned long> > X_listIdx;
    vector<pair<string, unsigned long> > X_xcount;
    pair<string , unsigned long> p;
    unsigned long n = -1;

    double prob; 
    mt19937 mt; 
    mt.seed(5381);
    // To get the random index to remove from X_xcount
    typedef uniform_int_distribution<> D;
    D d(0,S);

    ios::sync_with_stdio(false);
    string a;
    while(getline(cin, a)){
        if(a.empty()){
            a = "\n";
        }
        n += 1;
        if(n < S){
            p = pair<string, unsigned long>(a,1);
            X_xcount.push_back(p);
            // if(X_listIdx.find(a) != X_listIdx.end()){
            X_listIdx[a].push_back(n);       
            // } else {
            //      
            // }
        } else {
            prob = S/n;
            if(mt() < prob){
                //-----
                //Delete the old element
                //-----
                idx_to_del = d(mt);
                line_to_del = X_xcount[idx_to_del].first;
                X_listIdx[line_to_del].erase(remove(X_listIdx[line_to_del].begin(), X_listIdx[line_to_del].end(), idx_to_del), X_listIdx[line_to_del].end());
                if(X_listIdx[line_to_del].empty()){
                    X_listIdx.erase(X_listIdx.find(line_to_del));
                }
                //-----
                //Add the new element
                //-----
                p = pair<string, unsigned long>(a,1);
                X_xcount[idx_to_del] = p;
                X_listIdx[a].push_back(idx_to_del);
            } else {
                // line was not picked
                if(X_listIdx.find(a) != X_listIdx.end()){
                    for(auto idx: X_listIdx[a]){
                        X_xcount[idx].second += 1;
                    }
                }       
            }
        }
    }
    ofstream oFile;
    oFile.open(outputFile);
    unsigned long outVal;
    for(auto v: X_xcount){
        outVal = S * ( 2 * v.second - 1 );
        oFile << outVal << "\n";
        // cout << outVal << "\n"; 
    }
    oFile.close();
    return 0;
}
