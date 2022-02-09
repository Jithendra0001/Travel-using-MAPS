#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
#include<map>
#include<stdlib.h>
#include<unistd.h>
#define ll long long
using namespace std;
#define pb push_back
int From,To;

unordered_map<int,int>is_train_present;
unordered_map<int,int>plane;
int dis=INT_MAX;
int count=0;
int vis1[1000005]={false};
int vis2[1000005]={false};

vector<int>Shortest_Path;
vector<int>Maintains_Path;
vector<pair<int,int>>train;
int Extra_Train_Count=0;
int Train_Count=0;
vector<int>Bus_Path,h;
int x=INT_MAX;
int db=3,dt=2;

void Telangana()
{
cout<<"                   Nijamabad<-->Adilabad(T)"<<endl;
cout<<"                        //"<<endl;
cout<<"                  Hyderabad(T)<-->Warangal<-->Khammam"<<endl;
}
void Andhramap()
{
cout<<"            Kurnool       Kadapa"<<endl;
cout<<"          _____/  \\___________/__\\_____"<<endl;
cout<<"         /          /                 \\"<<endl;
cout<<"   Tirupati<-->Nellore(T)<-->Ongole<-->Guntur(T)<-->Vijayawada<-->Rajahmundry<-->Vizag<-->Vijayanagaram<-->Srikakulam(T)"<<endl;
    cout<<endl;
}
    /*
Map of Ts:               __Nijamabad<-->Adilabad(T)
                        /
                  ___Hyderabad(T)<-->Warangal<-->Khammam
   Map Of AP:    /                               |
               Kurnool       Kadapa              |
          _____/  \___________/__\_____          |
         /          /                 \          |
   Tirupati<-->Nellore(T)<-->Ongole<-->Guntur(T)<-->Vijayawada<-->Rajahmundry<-->Vizag<-->Vijayanagaram<-->Srikakulam(T)
    
    */
void output(map<int,string>Graph_Num)
{
    cout<<"Cheapest journey is:"<<endl;
    cout<<Graph_Num[Bus_Path[0]];
    for(int it=1;it<Bus_Path.size();it++) {cout<<"--(Bus)--> "<<Graph_Num[Bus_Path[it]];}
    cout<<"\nTime: "<<(Bus_Path.size()-1)*db<<endl;

    //Shortest_Path for train
    if(h.size()>1)
    Shortest_Path.insert(Shortest_Path.end()-1,h.rbegin(),h.rend()-1);
    vector<int>q;
    for(int i=0;i<Shortest_Path.size();i++)
    {
        if(is_train_present[Shortest_Path[i]]==1) q.pb(i);
    }
    int j=0,z=0;
    if(q.size()<2) {cout<<"No Trains available"<<endl;}
    else{
        cout<<"Hurray, trains are available !"<<endl;
    for(int i=0;i<Shortest_Path.size()-1;i++)
    {
        if(q[j]==i) {z=1;}
        if(z==0) cout<<Graph_Num[Shortest_Path[i]]<<"-->";
        if(z==1) {cout<<Graph_Num[Shortest_Path[q[j++]]]<<"-->";i=q[j]-1;if(j==q.size()) {z=0;i=q.back();}}
    }
    cout<<Graph_Num[To]<<endl;
    cout<<"Time: "<<dis<<endl;}
}
void From_Journey(map<int,string>Graph_Num)
{
    cout<<"/***********************Select From address:**********************/\n";
    cout<<"Select a district:\n";
    for(auto it:Graph_Num)
    {
        cout<<it.first+1<<") "<<it.second;
        if(is_train_present[it.first]==1) cout<<"( T )";
        cout<<endl;
    }
    int st;cin>>st;
    From=st-1;
    cout<<"/**********************Select To address:***********************/\n";
    cout<<"Select a district:\n";
    for(auto it:Graph_Num)
    {
        if(it.first==From) continue;
        if(it.first<From) cout<<it.first+1;
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
        if(is_train_present[p]==1) {Extra_Train_Count=Extra_Train_Count-((count-train.back().second)/db);return;}
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
        if(n==0) {n=q.size();Extra_Train_Count+=(db+dt);}
        if((count-train.back().second)/db<=Extra_Train_Count) {Extra_Train_Count=0;h.clear();return;}
    }
}
void gun(int &s)
{
    count-=db;
    vis2[s]=0;
    if(train.size()>0 && train.back().first==s) 
    {
        int ab=train.back().second;
        train.pop_back();
        if(train.size()>0)
        {
        int cd=train.back().second;
        Train_Count-=(ab-cd)/db;
        }
    }
    Maintains_Path.pop_back();
}
void Main_Function(vector<vector<int>>g,int s)
{
    vis1[s]=1;vis2[s]=1;
    Maintains_Path.pb(s);
    if(is_train_present[s]==1)
    {
        if(train.size()>0)
        {
            Train_Count+=(count-(train.back().second))/db;
        }
        train.pb({s,count});
    }
    if(s==To && x>Maintains_Path.size()) {Bus_Path=Maintains_Path;x=Bus_Path.size();}
    if(s==To && train.size()>0 && is_train_present[s]!=1 && (count-train.back().second)/db>(db+dt)) {alpha(g,s);}
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
            if(s==To) break;
            int t=g[s][i];
            if(vis1[t]==1 && vis2[t]==1) continue;
            count+=db;
            Main_Function(g,t);
        }
    gun(s);
}
void developer()
{
    cout<<"1) Change timing of bus."<<endl;
    cout<<"2) Change timing of train."<<endl;
    cout<<"3) Change both"<<endl;
    int ab;cin>>ab;
    if(ab==1)
    {
        cout<<"Enter time taken by bus to travel from one place to adjacent place.\n"<<endl;
        cin>>db;
    }
    if(ab==2)
    {
        cout<<"Enter time taken by train to travel from one place to adjacent place.\n"<<endl;
        cin>>dt;
    }
    if(ab==3)
    {
        cout<<"Enter time taken by bus to travel from one place to adjacent place.\n"<<endl;
        cin>>db;
        cout<<"Enter time taken by train to travel from one place to adjacent place.\n"<<endl;
        cin>>dt;
    }
}
int  main()
{
    /*
Map of Ts:               __Nijamabad<-->Adilabad(T)
                        /
                  ___Hyderabad(T)<-->Warangal<-->Khammam
   Map Of AP:    /                               |
               Kurnool       Kadapa              |
          _____/  \___________/__\_____          |
         /          /                 \          |
   Tirupati<-->Nellore(T)<-->Ongole<-->Guntur(T)<-->Vijayawada<-->Rajahmundry<-->Vizag<-->Vijayanagaram<-->Srikakulam(T)
    
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
    //TiruPathi
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
    int ran=1;
    cout<<"\nNOTE: BY DEFAULT, 'BUS' TAKES 3 UNITS OF TIME AND 'TRAIN' TAKES 2 UNITS OF TIME TO TRAVEL FROM ONE CITY TO ADJACENT CITY\n\n";
    sleep(3);
    while(ran)
    {
    // system("Color 0A");
    cout<<"__________Select an option____________"<<endl;
    cout<<"1) Show me the maps"<<endl;
    // cout<<"2) Show the map of Telangana."<<endl;
    cout<<"2) Start your Journey."<<endl;
    cout<<"3) Developer options"<<endl;
     int nitr;cin>>nitr;
     map<int,string>Graph_Num;
    //  system("Color 0B");
    for(auto it:hello)
    {
        Graph_Num[it.second]=it.first;
    }
    switch(nitr)
    {
        case 1:
            cout<<"_______Choose an option_______"<<endl;
            cout<<"1) Show me the map of Andhra pradesh"<<endl;
            cout<<"2) Show me the map of Telangana"<<endl;
            int map_count;cin>>map_count;
            if(map_count==1)
            Andhramap();
            else if(map_count==2)
            Telangana();
            break;
        case 3:
            developer();
            break;
        default:
            From_Journey(Graph_Num);
            int s=From;
            Main_Function(g,s);
            output(Graph_Num);
            break;           
    }
    cout<<"\n/********************Choose an option*********************/"<<endl;
    cout<<"\n1) Go to main menu"<<endl;
    cout<<"2) Exit"<<endl;
    cin>>ran;
    if(ran==2) ran=0;
    }
    cout<<"/****************Thank You for visiting.***************/"<<endl;
    return 0;
}
