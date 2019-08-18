#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
void erase(string n){
    std::ofstream ofs;
    ofs.open(n+".txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}
int main(){
    cout<<"enter the file name: ";
    string name;
    cin>>name;
    fstream file;
    file.open(name+".txt");
    string s;
    if(file) {
        ostringstream ss;
        ss << file.rdbuf(); // reading data
        s = ss.str();
    }
    cout<<s<<endl;
    lbl:
    cout<<"\noptions:\n1-erase file\n2-insert\n3-remove\n4-replace\n5-search\n6-append\n7-overwrite\n8-merge files\n";
    int option;
    cin>>option;
    switch(option){
        case 1: {
            erase(name);
        }break;
        case 2:{
            int position;
            cout<<"enter position to insert in: ";
            cin>>position;
            string s1=s.substr(0,position),s2=s.substr(position,s.size()-position),s3;
            cout<<"enter the text to insert: ";
            cin>>s3;
            s=s1+" "+s3+s2;
        }
            break;
        case 3:{
            cout<<"enter the starting position to remove from: ";
            int start,end;
            cin>>start;
            cout<<"enter the ending position to remove from: ";
            cin>>end;
            string s1=s.substr(0,start),s2=s.substr(end,s.size()-end);
            s=s1+s2;
        }
            break;
        case 4:{
            cout<<"enter the starting position to replace from: ";
            int start,end;
            cin>>start;
            cout<<"enter the ending position to replace from: ";
            cin>>end;
            string s1=s.substr(0,start),s2=s.substr(end,s.size()-end),s3;
            cout<<"enter the text to replace with: ";
            cin>>s3;
            s=s1+s3+s2;
        }
            break;
        case 5: {
            cout << "enter the text to search for: ";
            string s1;
            cin >> s1;
            size_t found = s.find(s1);
            if (found != -1) {
                cout << "First occurrence is " << found << endl;
            }
            else{
                cout<<"not found\n";
            }
        }
        break;
        case 6:{
            string text;
            cout<<"enter the text to append: ";
            cin>>text;
            s+=text;
        }break;
        case 7:{
            erase(name);
            cout<<"enter the text to overwrite in the file: ";
            string text;
            cin>>text;
            file<<text;
        }break;
        case 8:{
            cout<<"enter the file name to merge: ";
            string name2;
            cin>>name2;
            fstream file2;
            string s2;
            file2.open(name2+".txt");
            if(file2) {
                ostringstream ss;
                ss << file2.rdbuf(); // reading data
                s2 = ss.str();
            }
            s=s+" "+s2;
        }break;
        default: {
            cout << "enter a valid option\n";
            goto lbl;
        }break;
    }
    system("cls");
    cout<<s;
    cout<<"do you want to save?\nY-yes N-no C-cancel\n";
    char save;
    cin>>save;
    if(save=='y'||save=='Y'){
        cout<<"enter the file name: ";
        string n;
        cin>>n;
        if(n==name) {
            erase(name);
            file << s;
        }
        else{
            fstream file2;
            file2.open(n+".txt");
            file2<<s;
            file2.close();
        }
    }
    else if(save=='n'||save=='N'){
    }
    else{
        goto lbl;
    }
    file.close();
    return 0;
}
