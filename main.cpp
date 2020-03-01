#include <iterator>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <cassert>
#include <chrono>

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

//KMP implementation based codes on the Internet
class KMP {
    static int getNext(vector<int>& next, string const& str) {
        int len = str.size(), k = 0;
        for(int i = 1; i < len; i++) {
            while(k>0 && str[i]!= str[k]) k = next[k-1];
            next[i] = (k+=str[i]== str[k]);
        }
        return next[len-1];
    }

    static int match(string const& str, string const& pattern, vector<int> const& next) {
        int ans = 0, len1 = str.size(), len2 = pattern.size(), k =0;
        for(int i = 0; i < len1; i++) {
            while(k > 0 &&str[i] != pattern[k]) k = next[k-1];
            k += (str[i] == pattern[k]);
            if(k == len2) ans++;
        }
        return ans;
    }
public:
    static int count(string const& str,string const& pattern) {
        vector<int> next(pattern.size(), 0);
        getNext(next, pattern);
        return match(str, pattern, next);
    }
};

//Fast version with the suffix array
void fastFindAllRepeatedSubstr(string const& s, unordered_set<string>& v){
    vector<string> suffixArr;
    for(int i=0;i<s.size();++i){
        suffixArr.push_back(s.substr(i));
    }
    sort(suffixArr.begin(),suffixArr.end());
    for(int i=0;i<suffixArr.size()-1;++i){
        int k=0;
        int l=suffixArr[i].size(),r=suffixArr[i+1].size();
        while(k<l && k<r && suffixArr[i][k]==suffixArr[i+1][k]) ++k;
        if(k>1)
            v.insert(suffixArr[i].substr(0,k));
    }
}

//Naive version
void findAllRepeatedSubstr(string const& s, unordered_set<string>& v){
    int n=s.size();
    for(int i=0;i<n;++i){
        for(int j=i+1;j<n;++j){
            if(s[i]==s[j]){
               int k=1;
               while(i+k<n&&j+k<n&&s[i+k]==s[j+k]) ++k;
               if(k>1)
                   v.insert(s.substr(i,k));
            }
        }
    }
}

//Get substrs with most occurrences
void getRepeatedMost(string const& s, unordered_set<string> const& v, vector<string>& res){
    int maxTimes=0;
    for(string const& x: v){
        auto sum=KMP::count(s,x);
        if(sum>maxTimes){
            res.clear();
            maxTimes=sum;
            res.push_back(x);
        }
        else if(sum==maxTimes){
            res.push_back(x);
        }
    }

}

//Test function
void test(vector<string> const& cases){
    for(auto const& s:cases){
        cout<<endl;
        cout<<"[Test case] "<<s.substr(0,50)<<(s.size()>50?"... :":":")<<endl;
        cout<<"size: "<<s.size()<<endl;

        //Solution 1
        unordered_set<string> v1;
        vector<string> res1;
        {
            ScopedTimer timer;
            findAllRepeatedSubstr(s,v1);
            getRepeatedMost(s,v1,res1);
        }
        if(!res1.empty()){
            printVec(res1);
            cout<<endl;
        }


        //Solution 2
        unordered_set<string> v2;
        vector<string> res2;
        {
            ScopedTimer timer;
            fastFindAllRepeatedSubstr(s,v2);
            getRepeatedMost(s,v1,res2);
        }
        if(!res2.empty()){
            printVec(res2);
            cout<<endl;
        }

        //Test if results are the same
        assert(res1==res2);
    }
}

int main()
{
    //Stdin redirect
    freopen("input.txt","r",stdin);

    //Get input
    //NOTE: I use cin>> to get input, so the test string cannot contain spaces. This problem could be avoided
    //by using getline. Since it is trivial and has no impact on the result, I simply leave it out.
    vector<string> testCases;
    istream_iterator<string> iit(cin),eit;
    copy(iit,eit,back_inserter(testCases));

    //Test
    test(testCases);

    return 0;
}


