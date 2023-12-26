#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "sha256.h"
#include <bits/stdc++.h>


using namespace std;



class merkleNode
{
private:


public:
    merkleNode* levi;
    merkleNode* desni;
    string text;
    merkleNode(string t)
    {
        text=t;
        levi=NULL;
        desni=NULL;
    }
    merkleNode(merkleNode *l, merkleNode *d)
    {
        string s1="",s2="";
        if(l!=NULL) s1=(*l).t();
        if(d!=NULL) s2=(*d).t();
        text=sha256(s1+s2);
        levi=l;
        desni=d;
    }
    string t()
    {
        return text;
    }
    merkleNode * l()
    {
        return levi;
    }
    merkleNode * d()
    {
        return desni;
    }
    merkleNode rootpom(vector<merkleNode> niz)
    {


        int n=niz.size();
        cout<<"jebiga";
        cout<<n<<endl;
        if(niz.size()==2)
        {
            merkleNode goof1=niz[0];
            merkleNode goof2=niz[1];
            merkleNode res(&goof1,&goof2);
            cout<<"dosao do roota"<<endl;
            return res;
        }
        vector<merkleNode> pom;
        for(int i=0;i<n/2;i++)
        {
            merkleNode pom2(&niz[2*i],&niz[2*i+1]);
            pom.push_back(pom2);
        }
        if(n%2!=0)
        {
            cout<<"govnarii"<<endl;
            merkleNode pom2(&niz[n-1],NULL);
            pom.push_back(pom2);
        }
        cout<<"ide smraad"<<endl;
        merkleNode res=rootpom(pom);
        cout<<"smakored"<<endl;
        return res;
    }
    merkleNode(vector<string> niz)
    {
        int n=niz.size();
        vector<merkleNode> pom;
        for(int i=0;i<n;i++)
        {
            merkleNode pom1(sha256(niz[i]));
            pom.push_back(pom1);
        }
        merkleNode res=rootpom(pom);
        text=res.t();
        levi=(res.l());

        desni=(res.d());
    }

    void Prikaz()
    {
        cout<<text;
        cout<<"\n ovo je ovaj, a nodovi govani su mu deca evo: \n";
       // if(levi!=NULL) cout<<(levi->t()); else cout<<"bio null";
        cout<<"\n";/*
        cout << (*desni).t()<<endl;*/
        cout<<"govno jedno veliko usrano da bog da mu sve crklo";
        return;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<string> niz={ "00", "01", "02", "03" };
    merkleNode dummy("grr");
    merkleNode sr(niz);
    sr.Prikaz();

    cout << "Hello world!" << endl;
    return 0;
}
