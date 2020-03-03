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
    int mySqrt(int x) {
		//if(x==0) return 0;
		if(x==1) return 1;
		int left=0,right=x/2+1;
		while(left<right){
			int mid=((left+right)>>1);
			long long t=(long long)mid*(long long)mid;
			if(t==x) return mid;
			if(t<x)
			  left=mid+1;
			else
			  right=mid;
		}
		return left-1;
    }
};

int main()
{
    //Stdin redirect
    //freopen("input.txt","r",stdin);

    //istream_iterator<string> iit(cin),eit;
    //copy(iit,eit,back_inserter(testCases));
	
	vector<int> vec{9,9,9};

	Solution sol;
	auto const& v=sol.mySqrt(4);
	cout<<v<<endl;

    return 0;
}


