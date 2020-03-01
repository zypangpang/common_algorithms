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
	string bucketSort(string const& s){
		array<int,26> alphabet;
		alphabet.fill(0);
		for_each(s.begin(),s.end(),[&](char x){++alphabet[x-'a'];});
		string res;
		for(int i=0;i<26;++i){
			while(alphabet[i]--) res.push_back('a'+i);
		}
		return res;
	}
	vector<vector<string>> groupAnagrams1(vector<string>& strs) {
		vector<vector<string>> res;
		if(strs.empty()) return res;
		vector<string> tstrs=strs;
		for_each(tstrs.begin(),tstrs.end(),[=](string& s){
					bucketSort(s);});
		vector<int> index(strs.size());
		for(int i=0;i<strs.size();++i) index[i]=i;
		sort(index.begin(),index.end(),[&](int a,int b){
					return tstrs[a]<tstrs[b];});
		res.push_back(vector<string>{strs[index[0]]});
		for(int i=1;i<index.size();++i){
			if(tstrs[index[i]]==tstrs[index[i-1]]){
				res.back().push_back(strs[index[i]]);
			}else{
				res.push_back(vector<string>{strs[index[i]]});
			}
		}
		return res;
    }
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
		vector<vector<string>> res;
		if(strs.empty()) return res;
		unordered_map<string,vector<string>> strMap;
		for(auto const& s: strs){
			auto const& ss=bucketSort(s);
			strMap[ss].push_back(s);
		}
		for(auto const& v: strMap){
			res.push_back(v.second);
		}
		return res;
    }
};

int main()
{
    //Stdin redirect
    //freopen("input.txt","r",stdin);

    //istream_iterator<string> iit(cin),eit;
    //copy(iit,eit,back_inserter(testCases));

	vector<string> strs{"eat"};
	Solution sol;
	auto const& res=sol.groupAnagrams(strs);
	for(auto const& v:res){
		printVec(v);
		cout<<endl;
	}

    return 0;
}


