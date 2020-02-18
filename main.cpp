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
int lowerBound(vector<int> const& v,int x){
	int p=0,q=v.size();
	while(p<q){
		int m=p+(q-p)/2;
		if(v[m]>=x) q=m;
		else p=m+1;
	}
	return p;

}
int upperBound(vector<int> const& v,int x){
	int p=0,q=v.size();
	while(p<q){
		int m=p+(q-p)/2;
		if(v[m]<=x) p=m+1;
		else q=m;
	}
	return p;

}
int binarySearch(vector<int> const& v,int x){
	int p=0,q=v.size();
	while(p<q){
		int m=p+(q-p)/2;
		if(v[m]==x) return m;
		if(v[m]<x) p=m+1;
		else q=m;
	}
	return -1;

}
int main()
{
	//freopen("input.txt","r",stdin);
	//readGraph();
	vector<int> v{2,3,4,5,6};
	auto a=binarySearch(v,8);
	cout<<a<<endl;
    return 0;
}
