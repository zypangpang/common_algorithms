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
struct hash_pair { 
    template <class T1, class T2> 
    size_t operator()(const pair<T1, T2>& p) const
    { 
        auto hash1 = hash<T1>{}(p.first); 
        auto hash2 = hash<T2>{}(p.second); 
        return hash1 ^ hash2; 
    } 
}; 
	unordered_map<pair<int,int>,bool,hash_pair> mem;
	string _s,_p;
	bool match(int i,int j){
		if(mem.count({i,j})) return mem[{i,j}];
		if(i>=_s.size()){
			for(int k=j;k<_p.size();++k)
			  if(_p[k]!='*')
				return mem[{i,j}]=false;
			return mem[{i,j}]=true;
		}
		if(j>=_p.size()) return mem[{i,j}]=false;
		if(_p[j]=='?'||_p[j]==_s[i]) return mem[{i,j}]=match(i+1,j+1);
		if(_p[j]=='*'){
			for(int k=i;k<=_s.size();++k){
				if(match(k,j+1)) 
				  return mem[{i,j}]=true;
			}
		}
		return mem[{i,j}]=false;
	}
public:
    bool isMatch(string s, string p) {
		for(int i=0;i<p.size();++i){
			if(p[i]=='*'){
				int k;
				for(k=i+1;k<p.size();++k){
					if(p[k]!='*') break;
				}
				_p.push_back('*');
				i=k-1;
			}else
				_p.push_back(p[i]);
		}
		_s=s;
		cout<<_p<<endl;
		return match(0,0);
    }
};
int main()
{
	//freopen("input.txt","r",stdin);
	//readGraph();
	string s = "abc",p = "a***b***c***";
	Solution sol;
	cout<<sol.isMatch(s,p)<<endl;
    return 0;
}


