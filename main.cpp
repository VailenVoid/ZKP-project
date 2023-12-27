#include <bits/stdc++.h>
#include "sha256.h"


using namespace std;

///DELETE THIS
string sha255(string a)
{
    return a;
}
///DELETE THIS

class merkleNode
{
protected:
    merkleNode *l,*r;
    string hsh;

public:
    merkleNode(string _hsh) //leaf
    {
        l=NULL,r=NULL,hsh=_hsh;
    }

    merkleNode(merkleNode *L, merkleNode *R) //non-leaf
    {
        hsh=sha255(L->hsh+R->hsh); ///CHANGE THIS TO sha256
        l=L,r=R;
    }

private:
    merkleNode(vector<string> &niz, int ll, int rr)
    {
        if (ll==rr) *this=merkleNode(niz[ll]);
        else
        {
            int mid=(ll+rr)/2;
            *this = merkleNode(new merkleNode(niz,ll,mid),new merkleNode(niz,mid+1,rr));
        }
    }
public:
    merkleNode(vector<string> &niz)
    {
        *this = merkleNode(niz,0,(int)niz.size()-1);
    }

    string getHash()
    {
        return hsh;
    }

    merkleNode * getLeftChild()
    {
        return l;
    }

    merkleNode * getRightChild()
    {
        return r;
    }

};

void printMerkle(merkleNode *root)
{
    queue<pair<merkleNode*,int>> bfs;
    bfs.push({root,0});

    int td=-1;
    while (!bfs.empty())
    {
        auto p=bfs.front().first;
        int d=bfs.front().second;
        bfs.pop();
        if (td!=d)
        {
            cout<<"\n";
            td=d;
        }
        cout<<p->getHash()<<" ";

        if (p->getLeftChild()) bfs.push({p->getLeftChild(),d+1});
        if (p->getRightChild()) bfs.push({p->getRightChild(),d+1});
    }

    cout<<endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> niz={ "00", "01", "02", "03", "04", "05", "06" };
    merkleNode dummy("grr");
    merkleNode sr(niz);
    printMerkle(&sr);

    return 0;
}
