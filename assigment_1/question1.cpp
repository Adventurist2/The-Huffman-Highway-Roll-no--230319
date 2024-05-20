#include <iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    for(int i = 1;i<=n;i++)
    {
        for(int c = 1;c<=n;c++){
            if(c%2!=0){
            for (int j = 1;j<=n;j++){
                if(i>=j){
                    cout<<j;
                }else{cout<<" ";}
            }}
            else{
                for (int j = n;j>=1;j--){
                if(j<=i){
                    cout<<j;
                }else{cout<<" ";}
                }
            }
        }
        cout<<endl;

    }
    return 0;
}