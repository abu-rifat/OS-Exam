#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll num_p, num_r;
vector<ll>Available[1000], Max[1000], Allocation[1000], Need[1000], safeState;

void cal_need(){
    for(ll i=0;i<1000;i++)Need[i].clear();
    for(ll i=0;i<num_p;i++){
        for(ll j=0;j<num_r;j++){
            //cout<<"What?\n";
            ll val=Max[i][j]-Allocation[i][j];
            //cout<<"Oh\n";
            Need[i].push_back(val);
            cout<<Need[i][j]<<" ";
        }
        cout<<endl;
    }
}

bool ProcessRequest(ll p, vector<ll>instance){
    for(ll i=0;i<num_r;i++){
        if((instance[i]>Need[p][i])||(Available[p][i]<instance[i]))return false;
    }
    return true;
}

bool isSafe(){
    queue<ll>miss;
    ll idx=0;
    for(ll i=0;i<num_p;i++){
        ll ck=1;
        for(ll j=0;j<num_r;j++){
            if(Need[i][j]>Available[idx][j]){
                ck=0;
                break;
            }
        }
        if(ck==0){
            miss.push(i);
        }else{
            safeState.push_back(i);
            idx++;
            for(ll j=0;j<num_r;j++)Available[idx].push_back(Available[idx-1][j]+Allocation[i][j]);
        }
    }
    ll ct=0;
    while(!miss.empty()){
        if(ct>(num_p*4))return false;
        ll qp=miss.front();
        miss.pop();
        ll ck=1;
        for(ll j=0;j<num_r;j++){
            if(Need[qp][j]>Available[idx][j]){
                miss.push(qp);
                ck=0;
                break;
            }
        }
        if(ck==1){
            safeState.push_back(qp);
        }
    }
    return true;
}

 int main()
 {
    freopen("input.txt","r",stdin);
    cout<<"Enter the number of processes and number of resources:\n";
    ll n,m;
    cin>>num_p>>num_r;
    
    cout<<"Enter Available Resources:\n";
    for(ll i=0;i<1000;i++)Available[i].clear();
    for(ll i=0;i<num_r;i++){
        ll tmp;
        cin>>tmp;
        Available[0].push_back(tmp);
    }

    cout<<"Enter Allocation Matrix:\n";
    for(ll i=0;i<1000;i++)Allocation[i].clear();
    for(ll i=0;i<num_p;i++){
        for(ll j=0;j<num_r;j++){
            ll tmp;
            cin>>tmp;
            Allocation[i].push_back(tmp);
            cout<<Allocation[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<"Enter Max Matrix:\n";
    for(ll i=0;i<1000;i++)Allocation[i].clear();
    for(ll i=0;i<num_p;i++){
        for(ll j=0;j<num_r;j++){
            ll tmp;
            cin>>tmp;
            Max[i].push_back(tmp);
            cout<<Max[i][j]<<" ";
        }
        cout<<endl;
    }

    cal_need();

    cout<<"The Need Matrix:\n";
    for(ll i=0;i<num_p;i++){
        for(ll j=0;j<num_r;j++){
            cout<<Need[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;


    bool state=isSafe();
    if(state==true){
        cout<<"The system is in a safe state.\n";
        cout<<"A safe order:\n";
        for(ll i=0;i<num_p;i++){
            if(i!=0)cout<<" > ";
            cout<<"P"<<safeState[i];
        }
        cout<<endl;
    }

    cout<<"Enter the process to request:\n";
    string s;
    cin>>s;
    ll req_p=s[1]-'0';
    vector<ll>instance;
    for(ll i=0;i<num_r;i++){
        ll tmp;
        cin>>tmp;
        instance.push_back(tmp);
    }

    bool grant=ProcessRequest(req_p,instance);
    if(grant==true){
        cout<<"Request will be granted immidiately\n";
    }else{
        cout<<"Request won't be granted immidiately\n";
    }
    
     return 0;
 }