/*
Created by : Ahmad Mustafa Anis
Project Title : Student DataBase with Classes and Filing
working: creates and stores data of students and help them store in a file and apply different functions on it like adding/appending/searching/sorintg/deletion etc.
*/
#include <iostream>
#include <fstream>
using namespace std;
class Student {
	int reg, marks;
	//string name; error due to serializations
	//https://coliru.stacked-crooked.com/a/9d650349a70d80ab string can not be trivally copied
	/*
	Another Answer on StackOver Flow
	"your class contains std::string members.
	These are not plain old data types and typically hold pointers to dynamically allocated memory.
	You can't read and write your class as a unit and hope the std::string members and their contents will be properly constructed.
	The same may apply to the Time and Data members but you haven't shown how they're defined.
	You need to look into proper serialization."
	*/
public:
	Student(int rg=0,int mark=0):reg(rg),marks(mark){}
	void newDB();
	void outDB();
	int returnREG();
};

void Student::newDB() {
	
	cout << "\nWHAT IS REG #\t";
	cin >> reg;
	cout << "WHAT IS MARKS\n";
	cin >> marks;
}
void Student::outDB()
{
	cout << "\n------------------------------------\n"
		<< "REG # IS\t" << reg << endl
		<< "MARKS IS\t" << marks << endl;
}
int Student::returnREG()
{
	return reg; //returns registration no (private member of class)
}
void saveData(Student classOOP[], int& nn)
{
	ofstream outFile;
	if (!outFile)
	{
		cout << "FILE NOT LOADED\n";
		exit(-1);
	}
	outFile.open("std.DAT", ios::out | ios::binary);
	outFile.write((char*)&nn, sizeof(int)); //writes no of students in 1st 4bytes
	outFile.write((char*)classOOP,nn*sizeof(Student)); //writes complete array in file
	outFile.close();
}
void loadData(Student classOOP[], int& nn)
{
	ifstream outFile;
	outFile.open("std.DAT", ios::in | ios::binary);
	if (!outFile)
	{
		cout << "FILE NOT LOADED\n";
		exit(-1);
	}
	outFile.read((char*)&nn, sizeof(int)); //reads no of students from file stored in 1st 4 bytes
	outFile.read((char*)classOOP, nn * sizeof(Student)); //reads whole complete array
	outFile.close();
}
void update()
{
	fstream inOutFile;
	Student s1;
	int size, tempReg;
	bool check = false;
	inOutFile.open("std.dat", ios::in | ios::out | ios::binary);
	if (!inOutFile)
	{
		cout << "FILE NOT LOADED\n";
		exit(-1);
	}
	inOutFile.read((char*)&size, sizeof(int)); //noOf Students stored in 1st 4 bytes from filr
	cout << "What is REG # you want to update\n";
	cin >> tempReg; //reg no user wants to delete stored in temprary var
	for (int i = 0; i < size; i++)
	{
		inOutFile.read((char*)&s1, sizeof(Student));// read data of size Student and save it in S1 (Student class obj)
		if (tempReg == s1.returnREG()) //Compares with return function that if both reg # are equal, update that reg # and save data in file
		{
			check = true;
			s1.newDB();
			inOutFile.seekg(-8, ios::cur); //since pointer is at end of that object we have read so we have to move it backwards 8byte(size of our student class) to rewrite on previous obj
			inOutFile.write((char*)&s1, sizeof(Student));
			break;
		}
	}
	if (check == false)
	{
		cout << "Sorry REG # not Found\n";
\
	}
	inOutFile.close();
}
void search()
{
	ifstream outFile;
	Student s1;
	int size;
	int tempReg;
	bool check=false;
	outFile.open("std.dat", ios::in | ios::binary);
	if (!outFile)
	{
		cout << "FILE NOT LOADED\n";
		exit(-1);
	}
	outFile.seekg(0, ios::beg);
	cout << "Type REG # you want to search\n";//reg # user wants to search in temprory variable
	cin >> tempReg;
	outFile.read((char*)&size, sizeof(int));//size of array from file stored in size var
	for (int i = 0; i < size; i++)
	{
		outFile.read((char*)&s1, sizeof(Student));// read data of size Student and save it in S1 (Student class obj)
		if (tempReg == s1.returnREG()) //if reg of s1 and what user has given is equal , output that result
		{
			check = true;
			break;
		}
	}
	if (check == true)
	{
		s1.outDB();
	}
	else
		cout << "REG # NOT FOUND\n";


	outFile.close();
}

void del(Student s1[], int& nn)
{
	//we have to load whole data in order to move upcoming entites 1 step backwards after deleting a specific data
	char choice;
	fstream inOutFile;
	int size, tempReg;
	bool check = false;
	inOutFile.open("std.dat", ios::in | ios::out | ios::binary);
	if (!inOutFile)
	{
		cout << "FILE NOT LOADED\n";
		exit(-1);
	}
	cout << "HAVE you loaded Data or Input it 'Y' for Yes 'N' for NO\n";
	cin >> choice;
	if (choice == 'Y')
	{
		cout << "REG # you want to Delete\n";
		cin >> tempReg;
		for (int i = 0; i < nn; i++)
		{
			if (tempReg == s1[i].returnREG())
			{
				check = true;
				for (int j = i; j < nn-1; j++)
				{
					s1[j] = s1[j + 1];
				}
				break;
			}
		}
	}
	else {

		loadData(s1, nn);
		cout << "What is REG # you want to Delete\n";
		cin >> tempReg;
		for (int i = 0; i < nn; i++)
		{
			if (tempReg == s1[i].returnREG())
			{
				check = true;
				for (int j = i; j < nn - 1; j++)
				{
					s1[j] = s1[j + 1];
				}
				break;
			}
		}
	}

	if (check == true)
	{
		cout << "RECORD DELETED SUCCSSFULLY\n";
		nn--;
	}
	else
		cout << "SORRY REG # NOT FOUND\n";
	
}
void sort(Student arr[], int nn)
{
	for (int i = 0; i < nn; i++)
	{
		for (int j = i; j < nn; j++)
		{
			if (arr[i].returnREG() > arr[j].returnREG())
			{
				swap(arr[i], arr[j]);
			}
		}
	}
}
void addNewRecord()
{
	Student s1;
	fstream newRec;
	int nn;

	newRec.open("std.dat", ios::in | ios::app | ios::binary);
	if (!newRec)
	{
		cout << "FILE NOT LOADED\n";
		exit(-1);
	}
	cout << "DATA OF NEW STUDENT\n";
	s1.newDB();
	newRec.seekg(0, ios::beg); //bringing get and put pointers to beggning
	newRec.seekp(0, ios::beg);
	newRec.read((char*)&nn, sizeof(int));//reading no of stds saved in 1st 4 bytes from file
	cout <<"prev no of std\n"<< nn;
	nn++;
	cout << nn;
	newRec.seekg(0, ios::beg); //bringing get and put pointers to beggning
	newRec.seekp(0, ios::beg);
	newRec.write(reinterpret_cast<char*>(&nn), sizeof(int)); //appending increased no of students in 1st 4 bytes of file saved in nn
	newRec.seekg(0, ios::end);// bringing get and put pointer to end 
	newRec.seekp(0, ios::end);
	newRec.write(reinterpret_cast<char*>(&s1), sizeof(Student)); // appending new record at end of file
	
	newRec.close();
	
}
int main()
{

	
	Student classOOP[35];
	int nOs=0;
	int choice;
	do {
		cout << "TYPE 1 for input\n2 for output\n3 for save data\n4 for load data\n5 to search single student\n6 to update\n7 to del any student data\n8 to add new record\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "How many Students are in CLASS\n";
			cin >> nOs;
			for (int i = 0; i < nOs; i++)
			{
				cout << "\nDATA OF STUDENT # \t" << i + 1<<endl;
				classOOP[i].newDB();
			}
			sort(classOOP, nOs);
			break;
		case 2:
			for (int i = 0; i < nOs; i++)
			{
				cout << "\nDATA OF STUDENT # \t" << i + 1<<endl;
				classOOP[i].outDB();
			}
			break;
		case 3:
			saveData(classOOP , nOs);
			break;
		case 4:
			loadData(classOOP, nOs);
			break;
		case 5:
			search();
			break;
		case 6:
			update();
			break;
		case 7:
			del(classOOP,nOs);
			saveData(classOOP, nOs);
			break;
		case 8:
			addNewRecord();
			break;
		default:
			break;
		}
	} while (choice != 9);
}