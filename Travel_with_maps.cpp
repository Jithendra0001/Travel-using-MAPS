#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
#include<map>
#include<stdlib.h>
#define ll long long
using namespace std;
#define pb push_back
int st,e;

unordered_map<int,int>m;

int dis=INT_MAX;
int count=0;
int vis1[1000005]={false};
int vis2[1000005]={false};

vector<int>path;
vector<int>v;
vector<pair<int,int>>train;
int chaitu=0;
int c=0;
vector<int>bus,h;
int x=INT_MAX;

void output(map<int,string>jithu)
{
    cout<<"Bus path is:"<<endl;
    cout<<jithu[bus[0]];
    for(int it=1;it<bus.size();it++) {cout<<" ~~> "<<jithu[bus[it]];}
    cout<<"\nDistance: "<<(bus.size()-1)*3<<endl;

    //Path for train
    if(h.size()>1)
    path.insert(path.end()-1,h.rbegin(),h.rend()-1);
    cout<<"Train path is"<<endl;
    vector<int>q;
    for(int i=0;i<path.size();i++)
    {
        if(m[path[i]]==1) q.pb(i);
    }
    int j=0,z=0;
    if(q.size()<2) {cout<<"No Train path available"<<endl;}
    else{
    for(int i=0;i<path.size();i++)
    {
        if(q[j]==i) {z=1;}
        if(z==0) cout<<jithu[path[i]]<<" ";
        if(z==1) {cout<<jithu[path[q[j++]]]<<" ";i=q[j]-1;if(j==q.size()) {z=0;i=q.back();}}
    }
    cout<<endl<<dis<<endl;}
}
void Start_Journey(map<int,string>jithu)
{
    cout<<"Select from address:\n";
    for(auto it:jithu)
    {
        cout<<it.first+1<<") "<<it.second;
        if(m[it.first]==1) cout<<"( T )";
        cout<<endl;
    }
    int start;cin>>start;
    st=start-1;
    cout<<"Select to address:\n";
    for(auto it:jithu)
    {
        if(it.first==st) continue;
        if(it.first<st) cout<<it.first+1;
        else cout<<it.first;
        cout<<") "<<it.second;
        if(m[it.first]==1) cout<<"( T )";
        cout<<endl;
    }
    int end;
    cin>>end;
    if(end<st) end--;
    e=end;
}
void Telangana()
{
cout<<"                   Nijamabad<-->Adilabad"<<endl;
cout<<"                        //"<<endl;
cout<<"                  Hyderabad<-->Warangal<-->Khammam"<<endl;
}
void Andhramap()
{
cout<<"            Kurnool       Kadapa"<<endl;
cout<<"          _____/  \\___________/__\\_____"<<endl;
cout<<"         /          /                 \\"<<endl;
cout<<"   Tirupati<-->Nellore<-->Ongole<-->Guntur<-->Vijayawada<-->Rajahmundry<-->Vizag<-->Vijayanagaram<-->Srikakulam"<<endl;
    cout<<endl;
}
void alpha(vector<vector<int>>g,int &s)
{

    queue<vector<int>>q;
    vector<int>cv;cv.pb(s);
    q.push(cv);
    unordered_map<int,int>wq;
    int n=q.size();
    while(n--)
    {
        h=q.front();q.pop();
        int p=h.back();
        if(m[p]==1) {c=c-((count-train.back().second)/3);return;}
        for(int i=0;i<g[p].size();i++)
        {
            int t=g[p][i];
            if(vis1[t]==1 && vis2[t]==1) continue;
            if(!wq[t]) {
                wq[t]=1;
                h.pb(t);
                q.push(h);
            }
        }
        if(n==0) {n=q.size();c+=5;}
        if((count-train.back().second)/3<=c) {c=0;h.clear();return;}
    }
}
void gun(int &s)
{
    count-=3;
    vis2[s]=0;
    if(train.size()>0 && train.back().first==s) 
    {
        int ab=train.back().second;
        train.pop_back();
        int cd=train.back().second;
        chaitu-=(ab-cd)/3;
    }
    v.pop_back();
}
void dfs(vector<vector<int>>g,int s)
{
    vis1[s]=1;vis2[s]=1;
    v.pb(s);
    if(m[s]==1)
    {
        if(train.size()>0)
        {
            chaitu+=(count-train.back().second)/3;
        }
        train.pb({s,count});
    }
    if(s==e && x>v.size()) {bus=v;x=bus.size();}
    if(s==e && train.size()>0 && m[s]!=1 && (count-train.back().second)/3>5) {alpha(g,s);}
    else c=0;
    if(s==e && count-chaitu+c<dis)
        {
            dis=count-chaitu+c;
            path=v;
            gun(s);
            return;
        }
    for(int i=0;i<g[s].size();i++)
    {
        int t=g[s][i];
        if(vis1[t]==1 && vis2[t]==1) continue;
        count+=3;
        dfs(g,t);
    }
    gun(s);
}
int  main()
{
    /*
Map of Ts:               __Nijamabad<-->Adilabad
                        /
                  ___Hyderabad<-->Warangal<-->Khammam
   Map Of AP:    /                               |
               Kurnool       Kadapa              |
          _____/  \___________/__\_____          |
         /          /                 \          |
   Tirupati<-->Nellore<-->Ongole<-->Guntur<-->Vijayawada<-->Rajahmundry<-->Vizag<-->Vijayanagaram<-->Srikakulam
    
    */
   m[0]=1;m[8]=1;m[3]=1;m[11]=1;m[15]=1;
   unordered_map<string,int>hello;
   hello["nellore"]=0;
   hello["Tirupati"]=1;
   hello["ongole"]=2;
   hello["Guntur"]=3;
   hello["Vijayawada"]=4;
   hello["Rajahmundry"]=5;
   hello["Vizag"]=6;
   hello["Vizayanagaram"]=7;
   hello["srikakulam"]=8;
   hello["Kurnool"]=9;hello["Kadapa"]=10;
    hello["Hyderabad"]=11;hello["Warangal"]=12;
    hello["Khammam"]=13;hello["Nijamabad"]=14;hello["Adilabad"]=15;
    int n=1000005;
    vector<vector<int>>g(n);
    g[11].pb(9);
    g[11].pb(12);
    g[11].pb(14);

    g[12].pb(11);g[12].pb(13);

    g[13].pb(4);g[13].pb(12);

    g[14].pb(11);g[14].pb(15);

    g[15].pb(14);
    //Kadapa
    g[10].pb(0);g[10].pb(9);g[10].pb(3);
    //Kurnool
    g[9].pb(1);g[9].pb(0);g[9].pb(10);g[9].pb(11);
    //Nellore
    g[0].pb(1);
    g[0].pb(2);
    g[0].pb(10);
    g[0].pb(9);
    //Tirupathi
    g[1].pb(0);
    g[1].pb(9);
    //Ongole
    g[2].pb(0);
    g[2].pb(3);
    //Guntur
    g[3].pb(2);
    g[3].pb(4);
    g[3].pb(10);
    //Vijayawada
    g[4].pb(13);
    g[4].pb(5);
    g[4].pb(3);
    //Rajahmundry
    g[5].pb(4);
    g[5].pb(6);
    //Visakhapatnam
    g[6].pb(5);
    g[6].pb(7);
    //Vijayanagaram
    g[7].pb(6);
    g[7].pb(8);
    //Srikakulam
    g[8].pb(7);

    system("Color 0A");
    cout<<"1) Show the map of Andhra Pradesh."<<endl;
    cout<<"2) Show the map of Telangana."<<endl;
    cout<<"3) Start your Journey."<<endl;
     int nitr;cin>>nitr;
     map<int,string>jithu;
     system("Color 0B");
    for(auto it:hello)
    {
        jithu[it.second]=it.first;
    }
    switch(nitr)
    {
        case 1:
            Andhramap();
            break;
        case 2:
            Telangana();
            break;
        default:
            Start_Journey(jithu);
            int s=st;
            dfs(g,s);
            output(jithu);
    }

    return 0;
}
