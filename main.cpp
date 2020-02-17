#include <iterator>
#include <limits>
#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <algorithm>
#include <unordered_set>
#include <stack>
#include <unordered_map>

using namespace std;
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

class Solution {
	static const int INTMIN=numeric_limits<int>::min();
public:
struct MyTreeNode{
	int val=INTMIN;
	int upMax=INTMIN;
	int max=INTMIN;
	MyTreeNode *left=NULL;
    MyTreeNode *right=NULL;
    MyTreeNode(int x) : val(x){}
};
MyTreeNode* copyTree(TreeNode* root){
	if(root==NULL) return NULL;
	auto t=new MyTreeNode(root->val);
	t->left=copyTree(root->left);
	t->right=copyTree(root->right);
	return t;
}
void getMaxPath(MyTreeNode* root){
	if(root==NULL) return;
	if(root->left !=NULL) getMaxPath(root->left);
	if(root->right !=NULL) getMaxPath(root->right);
	int lu=root->left==NULL?root->val:root->val+root->left->upMax;
	int ru=root->right==NULL?root->val:root->val+root->right->upMax;
	root->upMax=max({root->val,lu,ru});
	int threeSome=root->val;
	if(root->left!= NULL) threeSome+=root->left->upMax;
	if(root->right!=NULL) threeSome+=root->right->upMax;
	root->max=max({root->upMax,root->left==NULL?INTMIN:root->left->max,root->right==NULL?INTMIN:root->right->max,threeSome});
}
    int maxPathSum(TreeNode* root) {
		auto myRoot=copyTree(root);
        getMaxPath(myRoot);
		return myRoot->max;
    }
};
TreeNode* createTree(vector<int> const& s,int& rootIndex){
	++rootIndex;
	if(s[rootIndex]==numeric_limits<int>::max()){ 
		return NULL;
	}
	TreeNode* root=new TreeNode(s[rootIndex]);
	root->left=createTree(s,rootIndex);
	root->right=createTree(s,rootIndex);
	return root;
}
const int MAXINT=numeric_limits<int>::max();
int main()
{
	vector<int> t{-10,9,MAXINT,MAXINT,-10,15,MAXINT,MAXINT,7,MAXINT,MAXINT};
	int r=-1;
	auto root=createTree(t,r);
	Solution s;
	auto res=s.maxPathSum(root);
	cout<<res<<endl;
    return 0;
}
