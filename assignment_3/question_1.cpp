#include <bits/stdc++.h>
#include <vector>
using namespace std;

class student{
    public:
    string Name;
    int Rollno ;
    string course;
    int marks;
    student(string name,int rollno,string course,int marks){
        this->Name = name;
        this->marks = marks;
        this->Rollno = rollno;
        this->course = course;
    }

};
class student_record
{
    private:
    vector <student> student_rec;
    vector <int> rnum;
    public:
    void create_record(string name,int rollno,string course,int marks){
        student newstudent(name,rollno,course,marks);
        rnum.push_back(rollno);
        student_rec.push_back(newstudent);
    }
    void delete_record(int rollno){
        int index;
        auto it = find(rnum.begin(),rnum.end(),rollno);
        if(it!=rnum.end()){
        for(int i=0;i<rnum.size();i++){
            if(rnum[i]==rollno){
                index=  i;
                break;
            }
        }
        rnum.erase(it);
        student_rec.erase(student_rec.begin()+index);
        cout<<"Successfully deleted"<<endl;
    }
    else{
        cout<<"NO record found"<<endl;
    }}
    void show_records() {
        if (student_rec.empty()) {
            cout << "No records to display.\n";
            return;
        }

        for (const auto& student_ : student_rec) {
            cout << "Name: " << student_.Name
                 << ", Roll Number: " << student_.Rollno
                 << ", Course: " << student_.course
                 << ", Marks: " << student_.marks << "\n";
        }
    }
    void search_record(int rollno){
        int index;
        auto it = find(rnum.begin(),rnum.end(),rollno);
        if(it!=rnum.end()){
            index = it-rnum.begin();
            auto& student_ = student_rec[index];
            cout << "Record found: \n"
                 << "Name: " << student_.Name
                 << ", Roll Number: " << student_.Rollno // Changed rollno to Rollno
                 << ", Course: " << student_.course
                 << ", Marks: " << student_.marks << "\n";
        }
        else{
            cout<<"No record found"<<endl;
        }
    }
};
int main(){
    string name, course;
    int rollno;
    int marks,n;
    student_record student_r;
    cout<<"Enter the number of records to entered"<<endl;
    cin>>n;
    for(int i=0;i<n;i++){
    cout << "Enter name: ";
    cin >> ws;  
    getline(cin, name);
    cout << "Enter roll number: ";
     cin >> rollno;
    cout << "Enter course: ";
    cin >> ws; 
    getline(cin, course);
    cout << "Enter marks: ";
    cin >> marks;
    student_r.create_record(name,rollno,course,marks);
    }
    student_r.show_records();
    student_r.search_record(230319);
    student_r.delete_record(2306997);
    student_r.search_record(2306997);
    student_r.show_records();
    
}
