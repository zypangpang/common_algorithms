#include <iterator>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <cassert>
#include <chrono>
#include <array>

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
    double myPow(double x, int n) {
		if(x==1||n==0) return 1;
		if(n==1) return x;
		if(n==-1) return 1/x;
		long long _n=n>0?n:-(long long)n;
		if(n<0){
			x=1/x;
		}
		double ans=1;
		double cur_prod=x;
		for(;_n;_n/=2){
			if(_n%2==1)
			  ans*=cur_prod;
			cur_prod*=cur_prod;
		}
		return ans;
    }
};
int main()
{
    //Stdin redirect
    //freopen("input.txt","r",stdin);

    //istream_iterator<string> iit(cin),eit;
    //copy(iit,eit,back_inserter(testCases));

	Solution sol;
	auto const& res=sol.myPow(1,numeric_limits<int>::min());
	cout<<res<<endl;

    return 0;
}


