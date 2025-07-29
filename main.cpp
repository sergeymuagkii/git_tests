#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void delete_spaces(string& str) {
	char c;
	for (int i=0; i<str.size(); i++) {
		char c = str[i];
		if (c == ' ') str[i] = '_';
	}
}

string create_spaces(string str) {
	char c;
	for (int i=0; i<str.size(); i++) {
		char c = str[i];
		if (c == '_') str[i] = ' ';
	}
	return str;
}

struct Person
	{
		string 
			first_name,
			last_name,
			phone_number,
			address;
	};

void init_person
	(
	Person& prs, string fName="Ivan", string lName="Ivanov", 
	string pNumber="0", string addr="komarovo 1"
	)
	{
		prs.first_name = fName;
		prs.last_name = lName;
		prs.phone_number = pNumber;
		prs.address = addr;
	}

void printInfo_person(Person& prs) {
	string addr_with_spaces = create_spaces(prs.address);

	cout << "First name\t: "	<< prs.first_name 	<< endl;
	cout << "Last name\t: " 	<< prs.last_name 	<< endl;
	cout << "Phone number\t: " 	<< prs.phone_number << endl;
	cout << "Address\t\t: " 	<< addr_with_spaces << endl;
}

istream& operator>>(istream& is, Person& prs) {
		
		string fName, lName, pNumber, addr;
		char 
			open_char/*{*/, closing_char/*}*/, 
			open_el_1/*(*/, closing_el_1/*)*/,
			open_el_2/*(*/, closing_el_2/*)*/,
			open_el_3/*(*/, closing_el_3/*)*/,
			open_el_4/*(*/, closing_el_4/*)*/; 
	
		is 
			>> open_char
			>> open_el_1 >> fName 	>> closing_el_1
			>> open_el_2 >> lName 	>> closing_el_2
			>> open_el_3 >> pNumber >> closing_el_3
			>> open_el_4 >> addr	>> closing_el_4
			>> closing_char
		;

		if (!is) return is;
		if 
			(
			open_char!='{' 		|| 
			closing_char!='}' 	|| 
			open_el_1!='(' 		||
			closing_el_1!=')'	||
			open_el_2!='(' 		||
			closing_el_2!=')'	||
			open_el_3!='(' 		||
			closing_el_3!=')'	||
			open_el_4!='(' 		||
			closing_el_4!=')'
			) 
		{
			is.clear(ios_base::failbit);
			return is;
		}

		init_person(prs, fName, lName, pNumber, addr);
		return is;
}


void write_persons_in_file(string& file_name, vector<Person>& persons) {
	ofstream ofs(file_name.c_str(), ios_base::app);
	if (!ofs) {
		cout << "Error in write file " << file_name << endl;
		return;
	}

	for (int i=0; i<persons.size(); i++) {
		ofs << "{ ";
		ofs << "( " << persons[i].first_name 	<< " ) ";
		ofs << "( " << persons[i].last_name 	<< " ) ";
		ofs << "( " << persons[i].phone_number 	<< " ) ";
		ofs << "( " << persons[i].address 		<< " ) ";
		ofs << "}\n";
	}
}

void read_persons_from_file(string& file_name, vector<Person>& persons) {
	
	Person prs;

	ifstream ifs(file_name.c_str());
	if (!ifs) {
		cout << "Error in read file " << file_name << endl;
		return;
	}

	persons.clear();
	while(ifs>>prs) {
		persons.push_back(prs);
	}
}


void show_peoples(string& file, vector<Person>& prs) {
	read_persons_from_file(file, prs);
	for (int i=0; i<prs.size(); i++) {
		printInfo_person(prs[i]);
		cout << endl;
	}
	prs.clear();
}

void create_new_people(string& file, vector<Person>& prs) {
	string first_name, last_name, phone_number, address;
	char sure = '?';
	Person pr;

	cout << "Enter first name: ";	cin >> first_name;
	cout << "Enter last name: ";	cin >> last_name;
	cout << "Enter phone number: "; cin >> phone_number;
	cin.ignore();
	cout << "Enter address: "; getline(cin, address);
	delete_spaces(address);

	cout << "Are you sure? (y/n) --> "; cin >> sure;
	if (sure == 'y') {
		init_person(pr, first_name, last_name, phone_number, address);
		prs.push_back(pr);
		write_persons_in_file(file, prs);
		prs.clear();
	}
	else {
		cout << "You didn't choose 'y'. Contact not added.";

	}

}


int main() {
	string data_file = "./shk.txt";
	vector<Person> persons;

	int vbr = 0;
	while(vbr!=200) {
		cout 
			<< "Hello, this is the address book!\n"
			<< "1. Add people\n"
			<< "2. Show peoples\n"
			<< "200. Quit\n"
			<< "\nPlase, input your choice >> "; cin >> vbr;
		cout << "-----------------------\n";

		switch (vbr) {
			case 1:
				create_new_people(data_file, persons);
				break;
			case 2:
				show_peoples(data_file, persons); 
				break;
			default:
				break;
		}

	}

	return 0;
}