string s;
int n;
 
struct state {
    int len, link;
    map<char, int> next;
};
 
const int MAXLEN = 100010;
state st[MAXLEN * 2];
int sz, last;
 
void sa_extend(char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    int p = last;
    while (p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}
 
void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
    sz++;
    last = 0;
 
    for(auto & e: s) sa_extend(e);
}
 
string p;
 
bool find_pattern(int i, int j){ // call find_pattern(0,0)
 
	bool ans = false;
	for(auto & e: st[i].next){
		//cout<<e.first<<" "<<p[j]<<endl;
		if(e.first == p[j]){
			if(j == (int)p.size()-1) return true;
			ans =  max(ans,find_pattern(e.second,j+1));
			
		}
	}
 
	return ans;
}
