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
    ListNode* mergeTwoListsRecur(ListNode* l1, ListNode* l2) {
		if(l1==NULL) return l2;
		if(l2==NULL) return l1;
		if(l1->val<l2->val){
			l1->next=mergeTwoListsRecur(l1->next,l2);
			return l1;
		}else{
			l2->next=mergeTwoListsRecur(l1,l2->next);
			return l2;
		}
	}
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		auto p=l1,q=l2;
		auto c=new ListNode(-1);
		c->next=l1;
		auto guard=c;
		while(p!=NULL||q!=NULL){
			if(p==NULL || q!=NULL && p->val>q->val){
				auto t=q;
				q=q->next;
				c->next=t;
				t->next=p;
				c=t;
			}
			else {
				p=p->next;
				c=c->next;
			}
		}
		return guard->next;
    }
};
int main()
{
	vector<int> v1{1,6,7};
	vector<int> v2{1,2,3};
	//freopen("input.txt","r",stdin);
	//readGraph();
	Solution solution;
	auto v=solution.mergeTwoListsRecur(createList(v1),createList(v2));
	printList(v);
    return 0;
}
