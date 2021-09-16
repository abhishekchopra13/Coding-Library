struct dsu
{
	vector<int> a, bulk;
	dsu(int n)
	{
		a.resize(n+1);
		bulk.resize(n+1,1);
		for(int i = 0; i <= n; i++) {
			a[i] = i;
		}
	};
	int root(int i)
	{
	    while(a[i] != i)
	    {
	        i = a[i];
	        a[i]= a[a[i]];
	    }
	    return i;
	}
	void merge(int x,int y)
	{
		if(root(x) == root(y))	
			return;
	    if(bulk[root(x)] >= bulk[root(y)]) {
	    	bulk[root(x)] += bulk[root(y)];
	    	a[root(y)] = a[root(x)];
	    } else {
	    	bulk[root(y)] += bulk[root(x)];
	    	a[root(x)] = a[root(y)];
	    }
	}
};