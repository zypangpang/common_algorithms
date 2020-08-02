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
#include <string>

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

class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
		if(numerator==0) return "0";
		
		bool negative=(numerator>0)^(denominator>0);

		long long remain=numerator,divide=denominator;
		if(remain<0) remain=-remain;
		if(divide<0) divide=-divide;

		unordered_map<long long,int> rMap;
		string ans;
		if(remain>divide){
			ans+=to_string(remain/divide);
			remain=remain%divide;
		}else{
			ans.push_back('0');
		}

		if(remain>0){
			ans.push_back('.');
		}

		while(remain>0 && rMap.find(remain)==rMap.end()){
			rMap[remain]=ans.size()-1;
			remain*=10;
			ans.push_back('0'+remain/divide);
			remain%=divide;
		}
		if(rMap.find(remain)!=rMap.end()){
			ans=ans.substr(0,rMap[remain]+1)+"("+ans.substr(rMap[remain]+1)+")";
		}

		return negative? "-"+ans:ans;
    }
};

int main(){
	int n=7,d=-12;
    Solution s;
	cout<<s.fractionToDecimal(n,d)<<endl;

	return 0;
}
