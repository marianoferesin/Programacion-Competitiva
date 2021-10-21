#include <bits/stdc++.h>
using namespace std;

typedef long long tint;
const int mxn = 1<<18; //cambiar
struct Data{
	tint s;
	Data(tint _s=0){//Neutro
		s = _s;
	}
	void merge(const Data& l,const Data& r){
		s = l.s+r.s;
	}
};
struct Lazy{
	tint sumar;
	Lazy(tint _sumar=0){//Neutro
		sumar=_sumar;
	}
	pair<Lazy,Lazy> split() const{ //divide en izq y der
		return {*this,*this};
	}
	void merge(const Lazy& lazy){//Acumula lazy en *this
		sumar += lazy.sumar;
	}
	void update(Data& d,tint tam) const{//Updatea Data con Lazy
		d.s += sumar*tam;
	}
};
struct lazyTree{
	Data data[2*mxn];
	Lazy lazy[2*mxn];
	int n;
	struct Nindex{
		int index,l,r; //[l,r] actual
		Nindex(int _index,int _l,int _r){ index=_index; l=_l; r=_r; }
		int size() const {	return r-l+1; }
		int mid() const { return (l+r)/2; }
		Nindex left() const { return Nindex(2*index,l,mid()); }
		Nindex right() const { return Nindex(2*index+1,mid()+1,r); }
	};
	Data* init(const int m){
		n = 1<<(32-__builtin_clz(m));
		for(int i=0;i<2*n;i++){
			data[i] = Data();
			lazy[i] = Lazy();
		}
		return (data+n);
	}
	void build(){
		for(int i=n-1;i>0;i--){
			data[i].merge(data[2*i],data[2*i+1]);
		}
	}
	void updateNode(const Lazy& w,const Nindex& nodo){
		lazy[nodo.index].merge(w);
		w.update(data[nodo.index],nodo.size());
	}
	void propagate(const Nindex& nodo){
		auto hijos = lazy[nodo.index].split();
		updateNode(hijos.first,nodo.left());
		updateNode(hijos.second,nodo.right());
		lazy[nodo.index] = Lazy();
	}
	Data query(int a,int b,const Lazy& w=Lazy()){return query(a,b,w,Nindex(1,0,n-1));}
	Data query(int a,int b,const Lazy& w,const Nindex& nodo){
		//[a,b] es la query - [l,r] es el rango actual
		if(nodo.r<a or nodo.l>b)
			return Data();
		if(a<=nodo.l and nodo.r<=b){
			updateNode(w,nodo);
			return data[nodo.index];
		}
		propagate(nodo);
		Data ret,hijoIzq,hijoDer;
		int mid = nodo.mid();
		if(a<=mid and b>=mid+1){ //Query esta en los dos hijos
			auto hijos = w.split();
			hijoIzq = query(a,mid,hijos.first,nodo.left());
			hijoDer = query(mid+1,b,hijos.second,nodo.right());
		}
		else{ //Uno va a retornar Data()
			hijoIzq = query(a,b,w,nodo.left());
			hijoDer = query(a,b,w,nodo.right());
		}
		data[nodo.index].merge(data[nodo.left().index],data[nodo.right().index]);
		ret.merge(hijoIzq,hijoDer);
		return ret;
	}
};

//https://www.urionlinejudge.com.br/judge/es/problems/view/1500
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int tt;
	cin>>tt;
	lazyTree t;
	while(tt--){
		int n,q;
		cin>>n>>q;
		t.init(n);
		while(q--){
			int aux,a,b,v;
			cin>>aux>>a>>b;
			if(aux){
				cout<<t.query(a-1,b-1).s<<'\n';
			}
			else{
				cin>>v;
				t.query(a-1,b-1,Lazy(v));
			}
		}
	}
	return 0;
}