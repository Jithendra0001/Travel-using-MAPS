#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
#include<map>
#include<stdlib.h>
#define ll long long
using namespace std;
#define pb push_back
int From,To;

unordered_map<int,int>is_train_present; 

int dis=INT_MAX;
int count=0;
int vis1[1000005]={false};
int vis2[1000005]={false};

vector<int>Shortest_Path;
vector<int>Maintains_Path;
vector<pair<int,int>>train;
int Train_Count=0;
int Extra_Train_Count=0;
vector<int>Bus_Path,h;
int x=INT_MAX;

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
void output(map<int,string>Graph_Num)
{
    cout<<"Bus_Path Shortest_Path is:"<<endl;
    cout<<Graph_Num[Bus_Path[0]];
    for(int it=1;it<Bus_Path.size();it++) {cout<<" ~~> "<<Graph_Num[Bus_Path[it]];}
    cout<<"\nDistance: "<<(Bus_Path.size()-1)*3<<endl;

    //Shortest_Path for train
    if(h.size()>1)
    Shortest_Path.insert(Shortest_Path.end()-1,h.rbegin(),h.rend()-1);
    cout<<"Train Shortest_Path is"<<endl;
    vector<int>q;
    for(int i=0;i<Shortest_Path.size();i++)
    {
        if(is_train_present[Shortest_Path[i]]==1) q.pb(i);
    }
    int j=0,z=0;
    if(q.size()<2) {cout<<"No Train Shortest_Path available"<<endl;}
    else{
    for(int i=0;i<Shortest_Path.size();i++)
    {
        if(q[j]==i) {z=1;}
        if(z==0) cout<<Graph_Num[Shortest_Path[i]]<<" ";
        if(z==1) {cout<<Graph_Num[Shortest_Path[q[j++]]]<<" ";i=q[j]-1;if(j==q.size()) {z=0;i=q.back();}}
    }
    cout<<endl<<dis<<endl;}
}
void From_Journey(map<int,string>Graph_Num)
{
    cout<<"Select from address:\n";
    for(auto it:Graph_Num)
    {
        cout<<it.first+1<<") "<<it.second;
        if(is_train_present[it.first]==1) cout<<"( T )";
        cout<<endl;
    }
    int st;cin>>st;
    From=st-1;
    cout<<"Select to address:\n";
    for(auto it:Graph_Num)
    {
        if(it.first==st) continue;
        if(it.first<st) cout<<it.first+1;
        else cout<<it.first;
        cout<<") "<<it.second;
        if(is_train_present[it.first]==1) cout<<"( T )";
        cout<<endl;
    }
    int e;
    cin>>e;
    if(e<From) e--;
    To=e;
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
        if(is_train_present[p]==1) {Extra_Train_Count=Extra_Train_Count-((count-train.back().second)/3);return;}
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
        if(n==0) {n=q.size();Extra_Train_Count+=5;}
        if((count-train.back().second)/3<=Extra_Train_Count) {Extra_Train_Count=0;h.clear();return;}
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
        Train_Count-=(ab-cd)/3;
    }
    Maintains_Path.pop_back();
}
void dfs(vector<vector<int>>g,int s)
{
    vis1[s]=1;vis2[s]=1;
    Maintains_Path.pb(s);
    if(is_train_present[s]==1)
    {
        if(train.size()>0)
        {
            Train_Count+=(count-train.back().second)/3;
        }
        train.pb({s,count});
    }
    if(s==To && x>Maintains_Path.size()) {Bus_Path=Maintains_Path;x=Bus_Path.size();}
    if(s==To && train.size()>0 && is_train_present[s]!=1 && (count-train.back().second)/3>5) {alpha(g,s);}
    else Extra_Train_Count=0;
    if(s==To && count-Train_Count+Extra_Train_Count<dis)
        {
            dis=count-Train_Count+Extra_Train_Count;
            Shortest_Path=Maintains_Path;
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
   is_train_present[0]=1;is_train_present[8]=1;is_train_present[3]=1;is_train_present[11]=1;is_train_present[15]=1;
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
    //TiruShortest_Pathi
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
    cout<<"3) From your Journey."<<endl;
     int nitr;cin>>nitr;
     map<int,string>Graph_Num;
     system("Color 0B");
    for(auto it:hello)
    {
        Graph_Num[it.second]=it.first;
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
            From_Journey(Graph_Num);
            int s=From;
            dfs(g,s);
            output(Graph_Num);
    }

    return 0;
}
