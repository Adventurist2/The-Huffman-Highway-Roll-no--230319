#include <iostream>
using namespace std;

string lexicographical_rotation(string s){
    // finding the smallest character
    int is;char min='z';
    for(int i=0;i<s.size();i++){
        if(s[i]<=min){
            min = s[i];
            is = i;
        }
    }
    if(is==0){
        return s;
    }
    else{
        s = s.substr(is)+s.substr(0,is);
        return s;
    }
}
int main(){
    string s;
    cout<<"Enter a string"<<endl;
    cin>>s;
    cout<<lexicographical_rotation(s)<<endl;
}