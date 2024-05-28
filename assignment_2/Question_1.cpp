#include <bits\stdc++.h>
using namespace std;
class transaction{
    public:
    string Date,Day;float T_Amount=0.0;
    transaction(string date="",string day="",float amt=0.0){
        Date = date;
        Day = day;
        T_Amount = amt;
    }

};
class Loan{
    public :
    string loan_Date,loan_Day;float loan_Amount=0.0,tol_loan = 0.0;
    Loan(string date="",string day="",float amt=0.0){
        loan_Date = date;
        loan_Day = day;
        loan_Amount = amt;
        tol_loan = amt;
    }
};
class Bank:public transaction,public Loan{
    private:
    long Account_no;
    string Name;
    string Address;
    string Type;
    float Funds = 0.0;
    vector<transaction> trans_his;
    vector<Loan> loan_his;
    float t_loan_amt = 0;
    public:
    Bank(string name,string address,long acc_n,string type,float amt,string date,string day) : transaction(date, day, amt), Loan(){
        Name = name;
        Address = address;
        Account_no = acc_n;
        Type = type;
        Funds += amt;
        trans_his.push_back(transaction(date,day,amt));
    }
    void deposite(float balance,string date,string day){
        Funds = Funds+balance;
        transaction t = transaction(date,day,balance);
        trans_his.push_back(t);
        cout<<"Name "<<Name<<endl<<"Address "<<Address<<endl<<"Account_no. "<<Account_no<<endl<<"fund deposited"<<endl<<endl;
    }
    void Withdraw(float amount,string date,string day)
    {
        Funds = Funds-amount;
        transaction t = transaction(date,day,amount);
        trans_his.push_back(t);
        cout<<"Name "<<Name<<endl<<"Address "<<Address<<endl<<"Account_no. "<<Account_no<<endl<<"fund withdrawn"<<endl<<endl;
    }
    void update(long account_no,string name,string address){
        Account_no = account_no;
        Name = name;
        Address = address;
        cout<<"Name "<<Name<<endl<<"Address "<<Address<<endl<<"Account_no. "<<Account_no<<endl<<endl;

    }
    void loan(string date,string day,float amt){
        Loan l(date, day, amt);
        t_loan_amt += amt;
        l.tol_loan = t_loan_amt;
        loan_his.push_back(l);
        cout<<"Date "<<l.loan_Date<<endl<<"Day "<<l.loan_Day<<endl<<"Loan amount "<<l.loan_Amount<<endl<<"Total loan"<<l.tol_loan<<endl<<endl;
        
    }
    void tranfer(Bank &reciever,long rec_acc_no,float transfer_amt,string d,string dy)
    {
        if(this->Account_no != rec_acc_no){
            reciever.Funds += transfer_amt;
            this->Funds -= transfer_amt;
            this->trans_his.push_back(transaction(d,dy,transfer_amt));
            reciever.trans_his.push_back(transaction(d,dy,transfer_amt));
        }
        else{
            cout<<"Invalid sender account no."<<endl<<endl;
        }
    }
    void Viewing_passbook(){
        cout<<"Account No.: "<<Account_no<<endl<<"Name of the Account Holder: "<<Name<<endl<<"Address : "<<Address<<endl<<endl;
    }
    void search_transaction_history(string date,float amt){
        int flag = 0;
        for(auto i :trans_his){
            if ( i.Date==date && i.T_Amount == amt){
                flag = 1;
                cout << "Transaction found: Date: " << i.Date << ", Day: " << i.Day << ", Amount: " << i.T_Amount << endl<<endl;
            }
            
        }
        if(!flag){
                cout <<"No such Transaction found"<<endl<<endl;
            }
    }
    void search_loan_history(string date,float amt){
        int flag = 0;
        for(auto i :loan_his){
            if ( i.loan_Date==date && i.loan_Amount == amt){
                flag = 1;
                cout << "Loan Transaction found: Date: " << i.loan_Date << ", Day: " << i.loan_Day << ", Amount: " << i.loan_Amount << endl<<endl;
            }

        }
                    if (!flag){
                cout <<"No such Loan Transaction found"<<endl<<endl;
            }
    }


};

int main(){
    Bank person1 = Bank("Chandan Achary","H-13 IITK",12345678,"Savings",0.0,"28-05-2024","Tuesday");
    Bank person2 = Bank("Gopal","Berhampur",13455678,"Savings",10.0,"28-05-2024","Tuesday");
    person1.Viewing_passbook();
    person2.Viewing_passbook();
    person1.deposite(2500.0,"28-05-2024","Tuesday");
    person1.Withdraw(500.0,"28-05-2024","Tuesday");
    person1.loan("28-05-2024","Tuesday",50000);
    person1.search_loan_history("28-05-2024",50000);
    person1.search_transaction_history("28-05-2024",2500.0);
    person1.tranfer(person2,12354678,200.0,"28-05-2024","Tuesday");
    person1.search_transaction_history("28-05-2024",200.0);
    person2.search_transaction_history("28-05-2024",200.0);
}
