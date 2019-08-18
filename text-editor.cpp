#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
void erase(string n) {
	std::ofstream ofs;
	ofs.open(n + ".txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}
int main() {
	cout << "enter the file name: ";
	string name;
	cin >> name;
	fstream file;
	file.open(name + ".txt");
	string s;
	if (file) {
		ostringstream ss;
		ss << file.rdbuf();
		s = ss.str();
	}
	cout << s << endl;
lbl:
	cout << "\noptions:\n1-erase file\n2-insert\n3-remove\n4-replace\n5-search\n6-append\n7-overwrite\n8-merge files\n";
	int option;
	cin >> option;
	switch (option) {
	case 1: {
		erase(name);
	}break;
	case 2: {
		int position;
		cout << "enter position to insert in: ";
		cin >> position;
		string s1 = s.substr(0, position), s2 = s.substr(position, s.size() - position+1), s3;
		cout << "enter the text to insert: ";
		cin.ignore();
		getline(cin, s3);
		s = s1 + " " + s3 + s2;
	}
			break;
	case 3: {
		cout << "enter the starting position to remove from: ";
		int start, end;
		cin >> start;
		cout << "enter the ending position to remove from: ";
		cin >> end;
		string s1 = s.substr(0, start), s2 = s.substr(end, s.size() - end+1);
		s = s1 + s2;
	}
			break;
	case 4: {
		cout << "enter the starting position to replace from: ";
		int start, end;
		cin >> start;
		cout << "enter the ending position to replace from: ";
		cin >> end;
		string s1 = s.substr(0, start), s2 = s.substr(end, s.size() - end+1), s3;
		cout << "enter the text to replace with: ";
		cin.ignore();
		getline(cin, s3);
		s = s1 + s3 + s2;
	}
			break;
	case 5: {
		cout << "enter the text to search for: ";
		string s1;
		cin.ignore();
		getline(cin, s1);
		size_t found = s.find(s1);
		if (found != -1) {
			cout << "First occurrence is " << found << endl;
		}
		else {
			cout << "not found\n";
		}
	}
			break;
	case 6: {
		string text;
		cout << "enter the text to append: ";
		cin.ignore();
		getline(cin, text);
		s = s + " " + text;
	}break;
	case 7: {
		erase(name);
		cout << "enter the text to overwrite in the file: ";
		string text;
		cin.ignore();
		getline(cin, text);
		file << text;
	}break;
	case 8: {
		cout << "enter the file name to merge: ";
		string name2;
		cin.ignore();
		getline(cin, name);
		fstream file2;
		string s2;
		file2.open(name2 + ".txt");
		if (file2) {
			ostringstream ss;
			ss << file2.rdbuf();
			s2 = ss.str();
		}
		s = s + " " + s2;
	}break;
	default: {

	}break;
	}
	system("cls");
	cout << s<<endl;
	cout << "save?\nY-yes N-no C-cancel\n";
	char save;
	cin >> save;
	if (save == 'y' || save == 'Y') {
		cout << "enter the name of file: ";
		string n;
		cin.ignore();
		getline(cin, n);
		if (name == n) {
			erase(n);
			file << s;
		}
		else {
			fstream file2;
			file2.open(n + ".txt");
			file2 << s;
			file2.close();
		}
	}
	else if(save=='n'||save=='N'){}
	else {
		goto lbl;
	}
	file.close();
	return 0;
}
