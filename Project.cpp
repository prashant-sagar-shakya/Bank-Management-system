#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <ctime>
using namespace std;

class bank
{
	int accNo;
	string name;
	string Fname;
	string Cnic;
	string P_no;
	string email;
	int amount;
	int newAmount;
	fstream file, file1;

public:
	int search;

	void createAccount(void);  // declaration of create account function
	void depositAmount(void);  // declaration of depositAmount function
	void withdrawAmount(void); // declaration of withdrawAmount function
	void checkInfo(void);	   // declaration of checkInfo function
};

int main()
{
	bank obj;
	char choice;

	cout << "\n\n\n\t\t......:::Prashant's Bank:::......";
	cout << "\n\t\t:: press 1 to Login  Account :: ";
	cout << "\n\t\t:: press 2 to Create Account ::";
	cout << "\n\t\t:: press 0 to Exit           ::";
	cout << "\n\t\t:: ......................... ::\n\t\t\t\t";
	cin >> choice;

	switch (choice)
	{
	case '1':
		cout << "Enter your account no :: ";
		cin >> obj.search;
		while (1)
		{
			cout << "\n\n\n\t\t.......:::Prashant's Bank:::.......";
			cout << "\n\t\t:: press 1 to Deposit  Amount  :: ";
			cout << "\n\t\t:: press 2 to Withdraw Amount  ::";
			cout << "\n\t\t:: press 3 to Check    Info    ::";
			cout << "\n\t\t:: press 0 to Exit     Menu    ::";
			cout << "\n\t\t:: ........................... ::\n\t\t\t\t";
			cin >> choice;

			switch (choice)
			{
			case '1':
				obj.depositAmount();
				break;
			case '2':
				obj.withdrawAmount();
				break;
			case '3':
				obj.checkInfo();
				break;
			case '0':
				return 0;
			default:
				cout << "Invalid Choice...!";
				break;
			}
			system("pause");
			system("cls");
		}
		break;
	case '2':
		obj.createAccount();
		break;
	case '0':
		exit(0);
	default:
		cout << "\n Invalid choice...! ";
		break;
	}
	return 0;
}

// Definition of createAccount function
void bank::createAccount()
{
	srand(time(0));
	accNo = rand();

	// Ensure unique account number
	file.open("data.txt", ios::in);
	if (file)
	{
		int bankAccNo;
		bool exists = false;
		while (file >> bankAccNo)
		{
			if (bankAccNo == accNo)
			{
				exists = true;
				break;
			}
			// Skip the rest of the line
			file.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		file.close();
		if (exists)
		{
			createAccount(); // Try again with a new account number
			return;
		}
	}

	cin.ignore();
	cout << "Enter Your name :: ";
	getline(cin, name);
	cout << "Enter Your Father name :: ";
	getline(cin, Fname);
	cout << "Enter Your Cnic :: ";
	getline(cin, Cnic);
	cout << "Enter Your phone no. :: ";
	getline(cin, P_no);
	cout << "Enter Your email :: ";
	getline(cin, email);
	cout << "Enter Your amount :: ";
	cin >> amount;

	cout << endl
		 << accNo << " This is your account number... \n";
	cout << "Please save it \n\n";

	file.open("data.txt", ios::out | ios::app);
	file << accNo << "\t\t" << name << "\t\t" << Fname << "\t\t" << Cnic << "\t\t" << P_no << "\t\t" << email << "\t\t" << amount << endl;
	file.close();
}

// Definition of depositAmount function
void bank::depositAmount()
{
	cout << "Enter amount to deposit :: ";
	cin >> newAmount;

	file.open("data.txt", ios::in);
	file1.open("data1.txt", ios::out | ios::app);

	bool found = false;
	while (file >> accNo >> name >> Fname >> Cnic >> P_no >> email >> amount)
	{
		if (accNo == search)
		{
			cout << "\nCurrent amount :: " << amount;
			amount += newAmount;
			cout << "\nUpdated amount :: " << amount << endl;
			found = true;
		}
		file1 << accNo << "\t" << name << "\t" << Fname << "\t" << Cnic << "\t" << P_no << "\t" << email << "\t" << amount << endl;
	}

	if (!found)
		cout << "Account not found!" << endl;

	file.close();
	file1.close();
	remove("data.txt");
	rename("data1.txt", "data.txt");
}

// Definition of withdrawAmount function
void bank::withdrawAmount()
{
	cout << "Enter amount to withdraw :: ";
	cin >> newAmount;

	file.open("data.txt", ios::in);
	file1.open("data1.txt", ios::out | ios::app);

	bool found = false;
	while (file >> accNo >> name >> Fname >> Cnic >> P_no >> email >> amount)
	{
		if (accNo == search)
		{
			if (newAmount > amount)
			{
				cout << "Insufficient balance!" << endl;
			}
			else
			{
				cout << "\nCurrent amount :: " << amount;
				amount -= newAmount;
				cout << "\nUpdated amount :: " << amount << endl;
			}
			found = true;
		}
		file1 << accNo << "\t" << name << "\t" << Fname << "\t" << Cnic << "\t" << P_no << "\t" << email << "\t" << amount << endl;
	}

	if (!found)
		cout << "Account not found!" << endl;

	file.close();
	file1.close();
	remove("data.txt");
	rename("data1.txt", "data.txt");
}

// Definition of checkInfo function
void bank::checkInfo()
{
	file.open("data.txt", ios::in);
	if (!file)
	{
		cout << "File opening error!";
		return;
	}

	bool found = false;
	while (file >> accNo >> name >> Fname >> Cnic >> P_no >> email >> amount)
	{
		if (accNo == search)
		{
			cout << "\n---------------------------\n";
			cout << endl
				 << "\t::: Account Number ::: " << accNo;
			cout << "\n\t::: User Name      ::: " << name;
			cout << "\n\t::: Father Name    ::: " << Fname;
			cout << "\n\t::: Cnic Number    ::: " << Cnic;
			cout << "\n\t::: Phone Number   ::: " << P_no;
			cout << "\n\t::: Email          ::: " << email;
			cout << "\n\t::: Current Amount ::: " << amount;
			cout << "\n---------------------------\n\n";
			found = true;
		}
	}

	if (!found)
		cout << "Account not found!" << endl;

	file.close();
}
