//en l queda guardado el lower bound;
//funcion de la forma 0 0 0 0 1 1 1 1 1
vector <int> v = {-8,-2,0,0,0,3,3,3,4,5,6,7};
int n = v.size();
int x = 4;
int l=0, r=n-1;
while(l<r){
	int mid = l+(r-l)/2;
    	
	if(v[mid] >= x) r = mid;
	else l = mid+1;
}
	    
cout<<"x: "<<x<<" -> "<<v[l]<<endl;
