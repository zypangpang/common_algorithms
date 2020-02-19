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
	const unsigned int INTMAX=(1<<31);
public:
    int divide(int dividend, int divisor) {
		long ldivisor=divisor,ldividend=dividend;
		if(divisor==1) return dividend;
		if(divisor == -1){
			if(dividend>=0) return -dividend;
			if(dividend==-INTMAX) return INTMAX-1;
			return -dividend;
		}
		bool sign=(dividend>0) ^ (divisor>0);
		int cnt =0;
		ldivisor=abs((long)divisor);
		ldividend=abs((long)dividend);
		while(ldivisor<=ldividend){
			++cnt;
			ldivisor<<=1;
		}
		int result=0;
		while(cnt>0){
			--cnt;
			ldivisor>>=1;
			if(ldivisor<=ldividend){
				result+=(1<<cnt);
				ldividend-=ldivisor;
			}
		}
		return sign?-result:result;
    }
};
int main()
{
	//freopen("input.txt","r",stdin);
	//readGraph();
	//vector<int> v{1,2,3,3,4,5,6,6};
	Solution s;
	auto a=s.divide(7,-2);
	cout<<a<<endl;
    return 0;
}


