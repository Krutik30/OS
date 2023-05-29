// Online C++ compiler to run C++ program online
#include <bits/stdc++.h>
using namespace std;
int main() {
    // Write C++ code here
    int n;
    cout<<"Enter number of process : ";
    cin>>n;
    float x,y;
    float timeLine = 0;
    int proC = 1;
    vector<pair<float , float>> q , p;
    queue<float> at;
    vector<float> ft;
    for(int i=0;i<n;i++){
        cout<<"Enter Arrival time and Burst time for Process number-"<<i<<" : ";
        cin>>x>>y;
        q.push_back(make_pair(x,y));
        p.push_back(make_pair(x,proC++));
    }
    sort(q.begin(), q.end());
    sort(p.begin(), p.end());
    cout<<"Pro : "; 
    for(auto i:p)
        cout<<i.second<<" ";
    cout<<"\nFT  : ";
    for(int i=0;i<n;i++){
        if(q[i].first > timeLine){
            timeLine += q[i].first - q[i-1].second;
        }
        timeLine += q[i].second;
        ft.push_back(timeLine);
        cout<<timeLine<<" ";
    }
    vector<float> tat,wt;
    cout<<"\nTAT : ";
    float sumTAT = 0 , sumWT = 0; 
    for(int i=0;i<n;i++){
        float t = ft[i] - q[i].first;
        tat.push_back(t);
        cout<<t<<" ";
        sumTAT+=t;
    }
    cout<<"\nWT  : ";
    for(int i=0;i<n;i++){
        float t = tat[i] - q[i].second;
        wt.push_back(t);
        cout<<t<<" ";
        sumWT += t;
    }
    cout<<"\nAvg TAT = "<<sumTAT/n<<endl;
    cout<<"Avg WT  = "<<sumWT/n<<endl;
    return 0;
}