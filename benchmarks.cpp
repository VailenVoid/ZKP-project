#include<bits/stdc++.h>
#include "merkletree.h"

using namespace std;

void human()
{
    int n;
    cout<<"Unesite broj elemenata niza: "<<flush;
    cin>>n;
    vector<string> s(n);
    cout<<"unesite niz hash-ova duzine "<<n<<" u narednom redu:"<<endl;
    for (int i=0;i<n;i++) cin>>s[i];

    merkleTree mt(s);

    cout<<"nastavite sa unosom upita"<<endl;
    cout<<"u svakom od narednih redova unosite jedan upit"<<endl;
    cout<<"ako uneste broj izmedju 0 i "<<n-1<<" upitali ste indeks niza da li je validan"<<endl;
    cout<<"ako unesete -1 zvanicno pocinje pravljenje dokaza na osnovu upita"<<endl;
    cout<<"ako unesete nesto drugo program ce vam verovatno puci"<<endl;
    cout<<"srecno! :)"<<endl<<endl;

    while (true)
    {
        int i; cin>>i;
        if (i==-1)
        {
            mt.processQueries();
        }
        else mt.addQuery(i);
    }
}

void autom()
{
    mt19937 rng(29042004);

    while (true)
    {
        cout<<"Unesite broj elemenata automatski generisanog niza i broj (slucajno generisanih) upita: "<<flush;
        int n,q; cin>>n>>q;

        vector<string> s(n);
        for (int i=0;i<n;i++) s[i]="abc";
        merkleTree mt(s);

        while (q--)
        {
            int i=rng()%n;
            mt.addQuery(i);
        }

        mt.processQueries();
        mt.destruct();
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    cout<<"Da li zelite da rucno unosite niz i upite? (y/n)"<<endl;
    char c; cin>>c; cout<<endl;
    if (c=='y' || c=='Y') human();
    else if (c=='n' || c=='N') autom();
    else return cout<<"Unsupported command, task terminated immediately!"<<endl,0;

    human();

    return 0;
}
