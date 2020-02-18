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
	vector<string> all;
	void generateParenthesisRecur(string s,int l,int r){
		if(l==0 && r==0){
			all.push_back(s);
			return;
		}
		if(r>l)
			generateParenthesisRecur(s+")",l,r-1);
		if(l>0)
			generateParenthesisRecur(s+"(",l-1,r);
	}
public:
    vector<string> generateParenthesis(int n) {
		generateParenthesisRecur("",n,n);
		return all;
    }
};
int main()
{
	//freopen("input.txt","r",stdin);
	//readGraph();
	Solution solution;
	auto all=solution.generateParenthesis(3);
	printVec(all);
    return 0;
}
