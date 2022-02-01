#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll num_p, num_r,hit=0,fault=0;

vector<ll>pages[1000];
vector<ll>references;
vector<bool>status;

ll getNxt(ll val, ll pos){
    ll dis=-1;
    for(ll i=pos;i<num_r;i++){
        if(references[i]==val){
            dis=i;
            break;
        }
    }
    return dis;
}

pair<bool,ll> getPos(ll idx){
    bool st=true;
    ll pos=0;
    ll ck=0;
    for(ll i=0;i<num_p;i++){
        if(references[idx]==pages[idx][i]){
            pos=i;
            ck=1;
            hit++;
            break;
        }
    }
    if(ck==0){
        for(ll i=0;i<num_p;i++){
            if(pages[idx][i]==-1){
                pos=i;
                fault++;
                st=false;
                ck=1;
                break;
            }
        }
    }
    if(ck==0){
        st=false;
        fault++;
        ll max_dis=INT_MIN;
        for(ll i=0;i<num_p;i++){
            ll dis=getNxt(pages[idx][i],idx+1);
            if(dis==-1)dis=INT_MAX;
            if(dis>max_dis){
                max_dis=dis;
                pos=i;
            }
        }
    }
    return {st,pos};
}

int main(){
    cout<<"Enter the number of pages:\n";
    cin>>num_p;
    cout<<num_p<<endl;
    cout<<"Enter the number of references:\n";
    cin>>num_r;
    cout<<num_r<<endl;
    cout<<"Enter the references:\n";
    for(ll i=0;i<num_r;i++){
        if(i!=0)cout<<" ";
        ll tmp;
        cin>>tmp;
        references.push_back(tmp);
        cout<<tmp;
    }
    cout<<"\n";
    cout<<"The Pages:\n";
    for(ll i=0;i<num_p;i++)pages[0].push_back(-1);
    for(ll i=0;i<num_r;i++){
        pair<bool,ll>stat=getPos(i);
        status.push_back(stat.first);
        ll idx=stat.second;
        if(idx>=num_p)idx=0;
        for(ll j=0;j<num_p;j++){
            if(idx==j){
                pages[i+1].push_back(references[i]);
            }else{
                pages[i+1].push_back(pages[i][j]);
            }
        }
    }
    for(ll i=0;i<num_r;i++){
        for(ll j=0;j<num_p;j++){
            cout<<pages[i+1][j]<<" ";
        }
        if(status[i]==true)cout<<": Hit\n";
        else cout<<": fault\n";
    }
    cout<<"\nTotal Number of Hits: "<<hit<<"\n";
    cout<<"\nTotal Number of Faults: "<<fault<<"\n";
    return 0;
}