#include <iterator>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <cassert>
#include <chrono>
#include <array>
#include <cmath>
#include <stack>
#include <queue>

using namespace std;

//Time Helper
struct ScopedTimer{
    chrono::high_resolution_clock::time_point start;
    ScopedTimer(){ start = chrono::high_resolution_clock::now(); }
    ~ScopedTimer(){
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        cout<<"<duration "<<duration.count()<<" us>"<<endl;
    }
};

ostream& operator<<(ostream& out, pair<int,int> const& p){
    out<<"("<<p.first<<","<<p.second<<")";
    return out;
}

template <typename T>
void printVec(T const& v,string split=" "){
    //copy(v.begin(),v.end(),ostream_iterator<T>(cout," "));
    for(auto const& x:v){
        cout<<x<<split;
    }
}

class LRUCache {
    int capacity;
    list<pair<int,int>> keyOrder;
    unordered_map<int,list<pair<int,int>>::iterator> keyValueMap;
public:
    LRUCache(int tcapacity): capacity(tcapacity) {
    }

    int get(int key) {
        if(keyValueMap.find(key) == keyValueMap.end()){
            return -1;
        }
        auto tpair=move(*(keyValueMap[key]));
        keyOrder.push_front(tpair);
        keyOrder.erase(keyValueMap[key]);
        keyValueMap[key]=keyOrder.begin();
        return keyOrder.begin()->second;
    }

    void put(int key, int value) {
        if(keyValueMap.find(key) != keyValueMap.end()){
            keyValueMap[key]->second=value;
            get(key);
            return;
        }
        if(keyOrder.size()==capacity){
            int eraseKey=keyOrder.back().first;
            keyOrder.pop_back();
            keyValueMap.erase(eraseKey);
        }
        keyOrder.push_front({key,value});
        keyValueMap[key]=keyOrder.begin();
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main(){
    map<pair<int,int>,int> a;
    a[{1,2}]=3;
    a[{3,4}]=5;
    for (auto x : a ) {
        cout<<x.first<<" ";
        cout<<x.second<<endl;
    }
    return 0;
}
