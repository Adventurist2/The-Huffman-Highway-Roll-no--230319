#include <iostream>
#include <algorithm>
using namespace std;
int main(){
    cout<<"Enter 10 exam score"<<endl;
    int arr[10];
    for(int i =0;i<10;i++){
        cin>>arr[i];

    }
    float avg; int n=0,n1=0;int s = 0;
    for(int i=0;i<10;i++){ s = s+arr[i];}
    avg = s/10.0;
    sort(arr,arr+10);
    for(int i=0;i<10;i++){
        if(arr[i]>(int)avg){n=n+1;}
        else if(arr[i]<(int)avg){n1 +=1;}

    }
    cout<<"Average Exam Score: "<<avg<<endl;
    cout<<"Highest Exam Score: "<<arr[9]<<endl;
    cout<<"Lowest Exam Score: "<<arr[0]<<endl;
    cout<<"Number of exam scores above the average: "<<n<<endl;
    cout<<"Number of exam scores below the average: "<<n1<<endl;
    return 0;
}