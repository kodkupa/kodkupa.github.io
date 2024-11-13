#include<iostream>
#include<string>
#include<cassert>

using namespace std;
void tc(){
    string s="abcde",ans="zzzzz";
    string found;
    for(int iter=0;iter<5;iter++){
        cout<<"? "<<s<<endl;
        string resp;
        cin>>resp;
        for(int i=0;i<5;i++){
            if(resp[i]!='W'){
                found.push_back('a'+iter*5+i);
            }
        }
        for(auto& it : s) it+=5;
    }
    for(int i=0;i<found.size() && i<4;i++){
        cout<<"? "<<string(5,found[i])<<endl;
        string resp;
        cin>>resp;
        for(int j=0;j<5;j++){
            if(resp[j]!='W'){
                ans[j]=found[i];
            }
        }
    }
    if(found.size()==5) for(auto& it : ans) if(it=='z') it=found[4];

    cout<<"! "<<ans<<endl;
}
int main()
{
    //assert(0);
    int t; cin>>t; while(t--)
        tc();
    return 0;
}
