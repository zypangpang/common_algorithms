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
    int removeDuplicates(vector<int>& nums) {
		if(nums.size()<2) return nums.size();
		int p=0;
		for(int q=1;q<nums.size();++q){
			if(nums[q]!=nums[p]) {
				++p;
				nums[p]=nums[q];
			}
		}
		return p+1;
		
    }
};
int main()
{
	//freopen("input.txt","r",stdin);
	//readGraph();
	vector<int> v{1,2,3,3,4,5,6,6};
	Solution s;
	auto a=s.removeDuplicates(v);
	cout<<a<<endl;
	printVec(v);
    return 0;
}


