struct Dsu
{
    vector<int> a, bulk;
    Dsu(int n)
    {
        a.resize(n + 1);
        bulk.assign(n + 1, 1);
        for(int i = 0; i <= n; i++) {
            a[i] = i;
        }
    };
    int root(int i) {
        while(a[i] != i) {
            i = a[i];
            a[i] = a[a[i]];
        }
        return i;
    }
    void merge(int x, int y) {
        int rx = root(x), ry = root(y);
        if(rx == ry)  
            return;
        if(bulk[rx] < bulk[ry]) {
            swap(rx, ry);
        }
        bulk[rx] += bulk[ry];
        a[ry] = a[rx];
    }
};