#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s;
    // cout<<"\n\nInput = ";
    s = "hi hello how do you do!";
    
    transform(s.begin(),s.end(),s.begin(),::toupper);
    cout<<endl<<"Uppercased = ";
    cout<<s<<endl;
    return 0;
}