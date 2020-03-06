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
/*template <typename Functor, typename ... Args>
auto runningTime(Functor f, Args && ... args)
    -> decltype(f(std::forward<Args>(args)...))
{
    //return std::function<R(Args...)>(f);
    ScopedTimer timer;
    return f(forward<Args>(args)...);
}*/


//Print helper
template <typename T>
void printVec(vector<T> const& v){
	copy(v.begin(),v.end(),ostream_iterator<T>(cout," "));
}
class Solution {
public:
    string minWindow(string s, string t) {
		unordered_map<char,int> m,tm;
		for(auto c:t){
			++tm[c];
			m[c]=0;
		}
		int charCnt=tm.size();
		int p=0,q=0,minWin=numeric_limits<int>::max(),sp=0,sq=0;
		int cnt=0;
		while(q<s.size()){
			auto c=s[q];
			++q;
			if(m.count(c)){
				++m[c];
				if(m[c]==tm[c]) ++cnt;
				while(p<q&&cnt==charCnt){
					auto x=s[p];
					if(m.count(x)){
						--m[x];
						if(m[x]<tm[x]){
							--cnt;
							if(q-p<minWin){
								minWin=q-p;
								sp=p;sq=q;
							}
						}
					}
					++p;
				}
			}
		}
		return s.substr(sp,sq-sp);
    }
};

int main()
{
    //Stdin redirect
    //freopen("input.txt","r",stdin);

    //istream_iterator<string> iit(cin),eit;
    //copy(iit,eit,back_inserter(testCases));
	string S = "aab", T = "aa";

	Solution sol;
	auto const& x=sol.minWindow(S,T);
	cout<<x<<endl;

    return 0;
}


