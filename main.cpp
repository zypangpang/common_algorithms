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
public:
    vector<vector<int>> permute(vector<int>& nums) {
		if(nums.empty()) return vector<vector<int>>();
		if(nums.size()==1) return vector<vector<int>>{nums};
		vector<vector<int>> resVec;
		sort(nums.begin(),nums.end());
		resVec.push_back(nums);
		int n=nums.size();
		while(1){
			int lp=-1;
			for(int i=0;i<n-1;++i){
				if(nums[i]<nums[i+1])
				  lp=i;
			}
			if(lp==-1) break;
			int lb=0;
			for(int i=lp+1;i<n;++i){
				if(nums[i]>nums[lp]) 
				  lb=i;
			}
			swap(nums[lp],nums[lb]);
			for(int i=1;i<=(n-lp)/2;++i){
				swap(nums[lp+i],nums[n-i]);
			}
			resVec.push_back(nums);
		}
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


