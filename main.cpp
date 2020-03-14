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
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
TreeNode* buildTree(vector<int> const& v,int& i){
	if(v[i]==-1)
	  return NULL;
	auto root=new TreeNode(v[i]);
	root->left=buildTree(v,++i);
	root->right=buildTree(v,++i);
	return root;
}
class Solution {
	bool isValid(TreeNode* root,long long& minE,long long& maxE){
		if(root==NULL){
			minE=numeric_limits<long long>::max();
			maxE=numeric_limits<long long>::min();
			return true;
		}
		long long minL,maxL,minR,maxR;
		auto l=isValid(root->left,minL,maxL);
		auto r=isValid(root->right,minR,maxR);
		if(!l||!r) return false;
		minE=min((long long)(root->val),min(minL,minR));
		maxE=max((long long)(root->val),max(maxL,maxR));
		if(maxL<root->val&&minR>root->val)
		  return true;
		else return false;
	}
public:
    bool isValidBST(TreeNode* root) {
		//long long a,b;
		long long cur=numeric_limits<long long>::min();
		//return isValid(root,a,b);
		return inOrder(root,cur);
    }
	bool inOrder(TreeNode* root,long long& cur){
		if(root==NULL) return true;
		if(!inOrder(root->left,cur)) return false;
		if(root->val<=cur) return false;
		cur=root->val;
		if(!inOrder(root->right,cur)) return false;
		return true;
	}
};
int main()
{

//[3,null,30,10,null,null,15,null,45]
    //Stdin redirect
    //freopen("input.txt","r",stdin);

    //istream_iterator<string> iit(cin),eit;
    //copy(iit,eit,back_inserter(testCases));
	
	//vector<int> v{2,1,-1,-1,3,-1,-1};
	vector<int> v{3,-1,30,10,-1,15,-1,45,-1,-1,-1};
	//vector<int> v{5,1,-1,-1,4,3,-1,-1,6,-1,-1};
	int i=0;
	auto root=buildTree(v,i);
	Solution sol;
	auto x=sol.isValidBST(root);
	cout<<x<<endl;

    return 0;
}


