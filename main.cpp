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

int getMinSub(vector<vector<int>> const& mat,int n){
    int res=0;
    for(int i=0;i<n-1;++i){
        int minVal=numeric_limits<int>::max();
        for(int j=0;j<3;++j){
            for(int k=0;k<3;++k){
                if(abs(mat[j][i]-mat[k][i+1])<minVal){
                    minVal=abs(mat[j][i]-mat[k][i+1]);
                }
            }
        }
        res+=minVal;
    }
}
long long getMin(vector<vector<int>> const& mat, int n ){
    vector<long long> minVal(3);
    for(int i=1;i<n;++i){
        vector<long long> t(3,numeric_limits<int>::max());
        for(int j=0;j<3;++j){
            for(int k=0;k<3;++k){
                long long x=abs((long long)mat[j][i]-(long long)mat[k][i-1])+minVal[k];
                if(x<t[j]){
                    t[j]=x;
                }
            }
        }
        minVal=t;
        //printVec(minVal);
        //cout<<endl;
    }
    return min(minVal[0],min(minVal[1],minVal[2]));
}
void fix(vector<vector<int>>& mat){
    int n=mat.size();
    int m=mat[0].size();
    vector<long long> row(n,numeric_limits<long long>::max());
    vector<long long> col(m,numeric_limits<long long>::max());
    for(int i=0;i<n;++i){
        for(int j=0;j<m-1;++j){
            if(mat[i][j]!=0&&mat[i][j+1]!=0){
                row[i]=(long long)mat[i][j+1]-(long long)mat[i][j];
            }
        }
    }
    for(int j=0;j<m;++j){
        for(int i=0;i<n-1;++i){
            if(mat[i+1][j]!=0&&mat[i][j]!=0){
                col[j]=(long long)mat[i+1][j]-(long long)mat[i][j];
            }
        }
    }
    for(int i=0;i<n;++i){
        if(row[i]!=numeric_limits<long long>::max()){
            int k=-1;
            for(k=0;k<m;++k){
                if(mat[i][k]!=0)
                    break;
            }
            if(k!=-1){
                for(int j=k-1;j>=0;--j){
                    mat[i][j]=mat[i][j+1]-row[i];
                }
                for(int j=k+1;j<m;++j){
                    mat[i][j]=mat[i][j-1]+row[i];
                }
            }
        }
    }
    for(int j=0;j<m;++j){
        if(col[j]!=numeric_limits<long long>::max()){
            int k=-1;
            for(k=0;k<n;++k){
                if(mat[k][j]!=0)
                    break;
            }
            if(k!=-1){
                for(int i=k-1;i>=0;--i){
                    mat[i][j]=mat[i+1][j]-col[j];
                }
                for(int i=k+1;i<n;++i){
                    mat[i][j]=mat[i-1][j]+col[j];
                }
            }
        }
    }
}
int main()
{

    //Stdin redirect
    //freopen("input.txt","r",stdin);

    //istream_iterator<string> iit(cin),eit;
    //copy(iit,eit,back_inserter(testCases));
    int n,m,q;
    cin>>n>>m>>q;
    vector<vector<int>> mat(n);
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            int t=0;
            cin>>t;
            mat[i].push_back(t);
        }
    }
    fix(mat);
    /*for(auto & x: mat){
        printVec(x);
        cout<<endl;
    }*/
    for(int i=0;i<q;++i){
        int x,y;
        cin>>x>>y;
        if(mat[x][y]==0)
            cout<<"Unknown"<<endl;
        else {
            cout<<mat[x][y]<<endl;
        }
    }

    return 0;
}


