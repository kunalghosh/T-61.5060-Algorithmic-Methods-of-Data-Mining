#include <ctime>
#include <iostream>
#include <unordered_map>
#define endl "\n"
using namespace std;

int main(){
    string a;
    unordered_map<string, long long> wordNCounts;
    ios::sync_with_stdio(false);
    time_t startF0 = std::time(nullptr);
    while(getline(cin,a)){
        if(a.empty()){
            a = "\n";
        }
        wordNCounts[a]++;
    }
    time_t startF2 = std::time(nullptr);
    cout << "F0 = " << wordNCounts.size() << endl;
    cout << "F0 Time = " << startF2 - startF0 << endl;
    long long F2 = 0;
    long long temp = 0;
    long long sizeStr = 0;
    long long sizeCounts = 0;
    for(auto w: wordNCounts){
        temp = w.second;
        F2 = F2 + (temp*temp);
        sizeStr = sizeStr + sizeof(w.first);
        sizeCounts = sizeCounts + sizeof(w.second);
    }
    time_t endF2 = std::time(nullptr);
    cout << "F2 = " << F2 << endl;
    cout << "Size = " << sizeStr + sizeCounts << " Bytes" << endl;
    cout << "F2 Time = " << endF2 - startF2 << endl;
    return 0;
}
