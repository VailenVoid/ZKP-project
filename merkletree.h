#ifndef MERKLETREE_H_INCLUDED
#define MERKLETREE_H_INCLUDED

#include <bits/stdc++.h>
#include "sha256.h"

using namespace std;

class merkleNode
{
private:
    string hsh;
public:
    merkleNode()
    {
        hsh="";
    }
    merkleNode(string s)
    {
        hsh=s;
    }
    string getHash()
    {
        return hsh;
    }
    merkleNode operator+ (merkleNode x)
    {
        merkleNode ret(sha256(hsh+x.hsh));
        return ret;
    }
};

class merkleTree
{
private:
    int k;
    vector<merkleNode> val;
    vector<int> id;
    vector<int> l,r;

    vector<int> queries;
    int idx=0;

    int depthK;
    int optimized_proof_size=0;
    int old_proof_size=0;

    bool Try(int p)
    {
        if (p==0) return true;
        if (id[p]==idx) return true;
        id[p]=idx;
        if (p<k)
        {
            optimized_proof_size++;
            if (val[p].getHash()!=(val[2*p]+val[2*p+1]).getHash()) return false;
            return Try(p/2);
        }
        return Try(p/2);
    }

public:
    merkleTree(vector<string> &niz)
    {
        k=1,depthK=1;
        int n=(int)niz.size();
        while (k<n) k*=2,depthK++;
        val.resize(2*k);
        l.resize(2*k);
        r.resize(2*k);
        id.resize(2*k);
        for (int i=0;i<k;i++) l[i+k]=i,r[i+k]=i;
        for (int i=k-1;i>0;i--) l[i]=l[2*i],r[i]=r[2*i+1];
        for (int i=0;i<n;i++) val[i+k]=merkleNode(niz[i]);
        for (int i=n;i<k;i++) val[i+k]=merkleNode();
        for (int i=k-1;i>0;i--) val[i]=val[2*i]+val[2*i+1];
        for (int i=1;i<2*k;i++) id[i]=0;
    }

    void destruct()
    {
        vector<merkleNode> tmp1;
        vector<int> tmp2,tmp3,tmp4;
        swap(val,tmp1);
        swap(l,tmp2);
        swap(r,tmp3);
        swap(id,tmp4);
        k=0;
    }

    void addQuery(int i)
    {
        queries.push_back(i);
    }

    void processQueries()
    {
        ++idx;
        optimized_proof_size=0;
        old_proof_size=0;
        for (auto it : queries)
        {
            Try(it+k);
            old_proof_size+=depthK;
        }

        queries.clear();

        cout<<"The old proof size would be: "<<old_proof_size<<endl;
        cout<<"The optimized proof size is: "<<optimized_proof_size<<endl;
        cout<<endl;
    }
};


#endif // MERKLETREE_H_INCLUDED
