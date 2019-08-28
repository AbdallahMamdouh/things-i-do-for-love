#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>
#include <sstream>
using namespace std;
class account {
private:
    string username, password;
    long balance;
public:
    account() {
        balance = 0;
    }
    account(string u, string p,long b=0) {
        username = u;
        password = p;
        balance = b;
    }
    void setUsername(string u) {
        username = u;
    }
    void setPassword(string p) {
        password = p;
    }
    string getUsername() {
        return username;
    }
    string getPassword(){
        return password;
    }
    void deposit(long b) {
        balance += b;
    }
    long checkBalance() {
        return balance;
    }
    void setBalance(long b) {
        balance = b;
    }
    void withdraw(long x){
        if(x<=balance) {
            balance -= x;
        }
    }
};
void delete_line(const char* file_name, int n)
{
    // open file in read mode or in mode
    ifstream is;
    is.open(file_name);
    // open file in write mode or out mode
    ofstream ofs;
    ofs.open("temp.txt", ofstream::out);

    // loop getting single characters
    char c;
    int line_no = 1;
    while (is.get(c))
    {
        // if a newline character
        if (c == '\n')
            line_no++;

        // file content not to be deleted
        if (line_no != n)
            ofs << c;
    }

    // closing output file
    ofs.close();

    // closing input file
    is.close();

    // remove the original file
    remove(file_name);

    // rename the file
    rename("temp.txt", file_name);
}
long string2long(string s) {
    long result = 0;
    long x = 1;
    for (int i = s.size() - 1; i >= 0; i--) {
        result += ((s[i] - '0') * x);
        x *= 10;
    }
    return result;
}
void partition(string s, string& u, string& p, long& d) {
    string temp;
    istringstream buf(s);
    buf>>u>>p>>temp;
    d=stol(temp);
}
void readPassword(string& s){
    char ch;
    ch = _getch();
    while (ch != 13) {//character 13 is enter
        s.push_back(ch);
        cout << '*';
        ch = _getch();
    }
}
int main() {
    ifstream in;
    ofstream out;
    in.open("database.txt", ios_base::app);
    out.open("database.txt", ios_base::app);
    vector<account> v;
lbl1:
    cout << "1-create a new account\n2-sign in\n";
    int option1;
    cin >> option1;
    system("cls");
    if (option1 == 1) {
        cout << "username: ";
        string username, password;
        cin >> username;
        cout << "password: ";
        readPassword(password);
        out << username << ' ' << password << ' ' << 0 << '\n';
        int option2;
        cout << "do another operation?\n1-yes\n0-no\n";
        cin >> option2;
        if (option2 == 1) {
            goto lbl1;
        }
        else {
            goto end;
        }
    }
    else if (option1 == 2) {
        account a;
       string username,password,s,u,p;
        long balance,b;
        while( getline(in,s)){
            partition(s,u,p,b);
            a.setUsername(u);
            a.setPassword(p);
            a.setBalance(b);
            v.push_back(a);
        }
        ofstream of;
        of.open("database.txt",ios::out|ios::trunc);
        of.close();
       lbl3:
        cout<<"username: ";
        cin>>username;
        cout<<"password: ";
        readPassword(password);
       bool found=false;
       for(int i=0;i<v.size();i++){
           if(username==v[i].getUsername()){
               found=true;
               if(v[i].getPassword()==password){
                   system("cls");
                   lbl2:
                   cout<<"\n1-deposit\n2-withdraw\n3-show balance\n";
                   int option2;
                   cin>>option2;
                   if(option2==1){
                       cout<<"how much to deposit: ";
                       int dep;
                       cin>>dep;
                       v[i].deposit(dep);
                   }
                   else if(option2==2){
                       cout<<"how much to withdraw: ";
                       long w;
                       cin>>w;
                       if(w<=v[i].checkBalance()) {
                           v[i].withdraw(w);
                       }
                       else{
                           cout<<"insufficient balance\n";
                           goto lbl2;
                       }
                       cout<<"you have withdrawn: "<<w<<" pounds\n";
                   }
                   else if(option2==3){
                       cout<<"balance: "<<v[i].checkBalance()<<endl;
                   }
                   else{
                       cout<<"enter a valid option\n";
                       goto lbl2;
                   }
                   break;
               }
               else{
                   cout<<"wrong password\n";
                   goto lbl3;
               }
           }
       }
       if(!found){
           cout<<"username not found\n";
           goto lbl3;
       }
       cout<<"do another operation?\n1-yes\n0-no\n";
       int option2;
       cin>>option2;
       if(option2==1){
           goto lbl1;
       }
       else{
           goto end;
       }
    }
    else {
        cout << "enter a valid option\n";
        goto lbl1;
    }
    end:
    for(int i=0;i<v.size();i++){
        out<<v[i].getUsername()<<' '<<v[i].getPassword()<<' '<<v[i].checkBalance()<<endl;
    }
    in.close();
    out.close();
}