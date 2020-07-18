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

ostream& operator<<(ostream& out, pair<int,int> const& p){
    out<<"("<<p.first<<","<<p.second<<")";
    return out;
}

template <typename T>
void printVec(T const& v,string split=" "){
    //copy(v.begin(),v.end(),ostream_iterator<T>(cout," "));
    for(auto const& x:v){
        cout<<x<<split;
    }
}
//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
	ListNode():val(0),next(NULL){}
};

ListNode* makeList(vector<int> const& t){
	ListNode* head=new ListNode();
	ListNode* tp=head;
	for(auto i: t){
		head->next=new ListNode(i);
		head=head->next;
	}
    return tp->next;
}

void printList(ListNode* head){
	for(;head!=NULL;head=head->next){
		cout<<head->val<<" ";
	}
}
class Solution {
    ListNode* mergeSort(ListNode* b){
    if(b->next==NULL) {
		return b;
	}
	//for(int i=0;i<n/2;++i) m=m->next;
	auto slow=b,fast=b->next;
	while(fast && fast->next){
		fast=fast->next->next;
		slow=slow->next;
	}
	auto m=slow->next;
	slow->next=NULL;

    b=mergeSort(b);
    m=mergeSort(m);

    ListNode* p=b,*q=m;
	ListNode* head=new ListNode(0);
	auto t=head;
    while(p!=NULL||q!=NULL){
		if(q==NULL||p!=NULL && p->val<q->val){
			t->next=p;
			p=p->next;
		}else{
			t->next=q;
			q=q->next;
		}
		t=t->next;
    }
	auto res=head->next;
	delete head;
    return res;
}
public:
    ListNode* sortList(ListNode* head) {
		if(head==NULL || head->next==NULL) return head;
        auto res=mergeSort(head);
        return res;
    }
};
int reverseNum=0;

int main(){
	vector<int> a{4,3,5,7};
    Solution s;
	auto t=makeList(a);
	printList(t);
	cout<<endl;

	/*
	auto fast=t->next;
	auto slow=t;
	while(fast && fast->next){
		slow=slow->next;
		fast=fast->next->next;
	}
	cout<<slow->val;
	cout<<endl;
	*/


    auto x=s.sortList(t);
    printList(x);
    return 0;
}
