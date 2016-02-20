#include <ctime>
#include <iostream>
#include <unordered_map>
#include <fstream>

#define endl "\n"
using namespace std;

void write_F0F2_to_file(string filename, long long F0, long long F2){
    ofstream fHandle(filename);
    fHandle << F0 <<" "<< F2;
    fHandle.close();
}
void read_F0F2_from_file(string filename, long long &F0, long long &F2){
    ifstream fHandle(filename);
    fHandle >> F0 >> F2;
    fHandle.close();
}

// Wouldn't compile in g++4.8 since it hasn't implemented moveable
// file streams. http://stackoverflow.com/questions/23176583/returning-an-fstream
// fstream getHandle(string filename){
//     fstream fHandle (filename);
//     return fHandle;  
// }

long long getFileSize(string filename){
    fstream fHandle(filename, ios::binary | ios::ate);
    long long size = fHandle.tellg();
    fHandle.close();
    return size;
}

int main(){

    long long F0 = 0;
    long long F2 = 0;
    long long F0_new = 0;
    long long F2_new = 0;
    long long F0_time = 0;
    long long temp = 0;
    long long sizeStr = 0;
    long long sizeCounts = 0;
    unsigned long map_size = 100000;

    string a;
    unordered_map<string, long long> wordNCounts;
    ios::sync_with_stdio(false);
    time_t startF0 = std::time(nullptr);
    while(getline(cin,a)){
        if(a.empty()){
            a = "\n";
        }
        if(wordNCounts.size() >= map_size){
            // don't add new strings to map
            if(wordNCounts.find(a) != wordNCounts.end()){
                wordNCounts[a]++;
            } else {
                cout << a << endl;
            }
        } else {
            wordNCounts[a]++;
        }
    }
    time_t startF2 = std::time(nullptr);
    F0_new = wordNCounts.size();
    F0_time = startF2 - startF0;

    // Starting to Calculate F2 now
    for(auto w: wordNCounts){
        temp = w.second;
        F2_new = F2_new + (temp*temp);
        sizeStr = sizeStr + sizeof(w.first);
        sizeCounts = sizeCounts + sizeof(w.second);
    }
    time_t endF2 = std::time(nullptr);

    string filename = "exactF0F2_multipass_data.txt";
    if(getFileSize(filename) != 0){
        read_F0F2_from_file(filename, F0, F2);
    }

    if(F0_new != 0){
        F0 = F0 + F0_new;
        F2 = F2 + F2_new;
        
        cerr << "F0 = " << F0 << endl;
        cerr << "F0 Time = " << F0_time << endl;
        cerr << "F2 = " << F2 << endl;
        cerr << "Size = " << sizeStr + sizeCounts << " Bytes" << endl;
        cerr << "F2 Time = " << endF2 - startF2 << endl;
        write_F0F2_to_file(filename, F0, F2);
        return 1;
    }
    cerr << "F0 = " << F0 << endl;
    cerr << "F0 Time = " << F0_time << endl;
    cerr << "F2 = " << F2 << endl;
    cerr << "Size = " << sizeStr + sizeCounts << " Bytes" << endl;
    cerr << "F2 Time = " << endF2 - startF2 << endl;
    cerr << "-- END --" << endl;
    remove(filename.c_str());
    return 0;
}
