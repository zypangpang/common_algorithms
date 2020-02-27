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
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
ListNode* createList(vector<int> const&  v){
	auto head=new ListNode(-1);
	auto p=head;
	for(auto a:v){
		p->next=new ListNode(a);
		p=p->next;
	}
	p=head->next;
	delete head;
	return p;
}
void printList(ListNode* head){
	for(;head!=NULL;head=head->next){
		cout<<head->val<<" ";
	}
}
class Solution {
	vector<vector<int>> resVec;
	void getPermutation(vector<int> & v, int first){
		if(first>=v.size()) {
			printVec(v);
			cout<<endl;
			resVec.push_back(v);
			return;
		}
		for(int i=first;i<v.size();++i){
			swap(v[i],v[first]);
			getPermutation(v,first+1);
			swap(v[i],v[first]);
		}
	}
public:
    vector<vector<int>> permute(vector<int>& nums) {
		if(nums.empty()) return vector<vector<int>>();
		if(nums.size()==1) return vector<vector<int>>{nums};
		getPermutation(nums,0);
		return resVec;
	}
};
int main()
{
	//freopen("input.txt","r",stdin);
	//readGraph();
	Solution sol;
	vector<int> a{1,2,3,4};
	sol.permute(a);
    return 0;
}


