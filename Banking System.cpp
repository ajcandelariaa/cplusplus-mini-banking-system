#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>

using namespace std;

struct People{
	char uname[30], pword[30], full_name[30];
};

void home();
void login();
void login_menu();
void registeration(struct People* info);

int main()
{
	People info;
	char home_choice;
	home();
	cin >> home_choice;
	while(home_choice != '1' && home_choice != '2' && home_choice != '3')
	{
		cout << "Invalid Input! Please enter the correct choice!" << endl;
		cout << "Choice: ";
		cin >> home_choice;
	}
	switch(home_choice)
	{
		case '1': system("cls"); registeration(&info); break;
		case '2': system("cls"); login(); break;
		case '3': system("pause"); exit(0); break;
	}
	system("pause");
	return 0;
}

void home()
{
	cout <<"===============================" << endl;
	cout <<"\tWELCOME  TO BANKING 101 " << endl;
	cout <<"===============================" << endl;   
	cout << "[1] Register" << endl;
	cout << "[2] Login" << endl;
	cout << "[3] Exit" << endl;
	cout << "Choice: ";
}

void registeration(struct People* info)
{
	char re_enter_pass[30], back_choice;
	int x = 3, entered_money;
	cout << "Registration" << endl;
	cout << "Fullname: ";
	cin.ignore();
	cin.getline(info->full_name, 30);
	cout << "Username: ";
	cin.getline(info->uname, 30);
	cout << "Password: ";
	cin.getline(info->pword, 30);
	cout << "Re-enter password: ";
	cin.getline(re_enter_pass, 30);
	while(strcmp(re_enter_pass, info->pword) != 0 && x > 0)
	{
		cout << "Password does not match! Please try again. You only have " << x  << " tries left." << endl;
		cout << "Re-enter password: ";
		cin.getline(re_enter_pass, 30);
		x--;
	}
	if(x == 0)
	{
		char try_choice;
		cout << endl << "No tries left!" << endl;
		cout << "[1] Home" << endl;
		cout << "[2] Exit" << endl;
		cout << "Choice: ";
		cin >> try_choice;
		switch(try_choice)
		{
			case '1': system("cls"); main(); break;
			case '2': system("pause"); exit(0); break;
		}
	}
	
	if(strcmp(re_enter_pass, info->pword) == 0)
	{
		cout << endl << endl;
		cout << "Password Match!" << endl;
		cout << "Card cost = P2000" << endl;
		cout << "Please enter your money for the payment of your card: ";
		cin >> entered_money;
		while(entered_money < 2000)
		{
			cout << "Not enough money. Please enter the exact amount or greater amount!" << endl;
			cout << "Please enter your money for the payment of your card: ";
			cin >> entered_money;
		}
		if(entered_money == 2000)
		{	
			cout << "Change: " << entered_money - 2000 << endl;
		}
		if(entered_money > 2000)
		{	
			cout << "Change: " << entered_money - 2000 << endl;
		}
		
		int x=0, balance=0;
		int temp_uname, temp_id;
	
		ifstream users_uname("Usernames.txt");
		while(users_uname >> temp_id >> temp_uname)
		{
			x = temp_id;
		}
		users_uname.close();
		
		ofstream add_fullname("Fullname.txt", ios::out | ios::app);
		ofstream add_uname("Usernames.txt", ios::out | ios::app);
		ofstream add_pword("Passwords.txt", ios::out | ios::app);
		ofstream add_balance("Balance.txt", ios::out | ios::app);
		
		add_fullname << info->full_name << endl;
		add_uname << x+1 << " " << info->uname << endl;
		add_pword << x+1 << " " << info->pword << endl;
		add_balance << x+1 << " " << balance << endl;
		
		add_fullname.close(); add_uname.close(); add_pword.close(); add_balance.close();
		cout << "Account Successfully Registered!" << endl;
		cout << "[1] Home" << endl;
		cout << "[2] Exit" << endl;
		cout << "Choice: ";
		cin >> back_choice;
		while(back_choice != '1' && back_choice != '2')
		{
			cout << "Invalid Input! Please enter the correct choice!" << endl;
			cout << "Choice: ";
			cin >> back_choice;
		}
		switch(back_choice)
		{
			case '1': system("cls"); main(); break;
			case '2': system("pause"); exit(0); break;
		}
	}
	
}

void login()
{
	char uname[30], pword[30];
	int check = 0, store_u_id, u_id;
	string r_uname, p_id, r_pword, r_fname, store_fullname;
	cout << "LOGIN" << endl;
	cout << "Username: ";
	cin.ignore();
	cin.getline(uname,30);
	cout << "Passowrd: ";
	cin.getline(pword, 30);	
	
	ifstream find_uname("Usernames.txt");
	ifstream find_pword("Passwords.txt");
	ifstream find_fullname("Fullname.txt");
	
	while(find_uname >> u_id >> r_uname && find_pword >> p_id >> r_pword && getline(find_fullname, r_fname))
	{
		if(uname == r_uname && pword == r_pword)
		{
			check = 1;
			store_u_id = u_id;
			store_fullname = r_fname;
		}
	}
	find_uname.close(); find_pword.close(); find_fullname.close();
	if(check == 1)
	{
		system("cls");
		char login_choice;
		int store_money;
		cout << "Login successfully!" << endl << endl << endl;
		login_menu_again:
		cout << "Welcome " << store_fullname << endl;
		login_menu();
		cin >> login_choice;
			while(login_choice != '1' && login_choice != '2' && login_choice != '3' && login_choice != '4')
			{
				cout << "Invalid Input! Please enter the correct choice!" << endl;
				cout << "Choice: ";
				cin >> login_choice;
			}
			if(login_choice == '1')
			{
				system("cls");
				int b_id, r_money;
				ifstream w_balance("Balance.txt");
				while(w_balance >> b_id >> r_money)
				{
					if(store_u_id == b_id)
					{
						store_money = r_money;
					}
				}
				w_balance.close();
					cout << "WITHDRAWAL" << endl;
				
					if(store_money <= 0)
					{
						char depo_choice;
						cout << "No balance. Please Proceed to deposit." << endl;
						cout << "[1] Deposit" << endl;
						cout << "[2] Back" << endl;
						cout << "[3] Exit" << endl;
						cout << "Choice: " << endl;
						cin >> depo_choice;
						while(depo_choice != '1' && depo_choice != '2' && depo_choice != '3')
						{
							cout << "Invalid Input! Please enter the correct choice!" << endl;
							cout << "Choice: ";
							cin >> depo_choice;
						}
						switch(depo_choice)
						{
							case '1': system("cls"); goto deposit; break;
							case '2': system("cls"); goto login_menu_again; break;
							case '3': system("pause"); exit(0); break;
						}
					}
					if(store_money > 0)
					{
						int choice_to_withdraw, total, with_id, with_money;
						char wi_choice;
						cout << "Balance: " << r_money << endl;
						cout << "How much do you want to withdraw: " << endl;
						cin >> choice_to_withdraw;
						while(choice_to_withdraw >= store_money)
						{
							cout << "Insufficient Balance. Please try lower" << endl;
							cout << "How much do you want to withdraw: " << endl;
							cin >> choice_to_withdraw;
						}
						total = r_money - choice_to_withdraw;
						cout << "Your Remaining Balance is: " << total << endl;
						
						ifstream with_update_balance("Balance.txt");
						ofstream tem1("temp.txt", ios::out | ios::app);
						while(with_update_balance >> with_id >> with_money)
						{
							if(store_u_id != with_id)
							{
								tem1 << with_id << " " << with_money << endl;
							}
						}
							tem1 << store_u_id << " " << total << endl;
								
							with_update_balance.close(); tem1.close(); 
					
							remove("Balance.txt");
							rename("temp.txt", "Balance.txt");
							
						cout << "[1] Back" << endl;
						cout << "[2] Exit" << endl;
						cout << "Choice: " << endl;
						cin >> wi_choice;
						while(wi_choice != '1' && wi_choice != '2')
						{
							cout << "Invalid Input! Please enter the correct choice!" << endl;
							cout << "Choice: ";
							cin >> wi_choice;
						}
						switch(wi_choice)
						{
							case '1': system("cls"); goto login_menu_again; break;
							case '2': system("pause"); exit(0); break;
						}
					}
			}
			if(login_choice == '2')
			{
				int choice_to_depo, depo_id, depo_bal, store_depo_bal, total;
				char de_choice;
				deposit:
					
				ifstream depo_balance("Balance.txt");
				while(depo_balance >> depo_id >> depo_bal)
				{
					if(depo_id == store_u_id)
					{
						store_depo_bal = depo_bal;
					}
				}
				depo_balance.close();
				
				cout << "DEPOSIT" << endl;
				cout << "How much do you want to deposit: " << endl;
				cin >> choice_to_depo;
				while(choice_to_depo <= 0)
				{
					cout << "Invalid Input, Please enter higher amount!" << endl;
					cout << "How much do you want to deposit: " << endl;
					cin >> choice_to_depo;
				}
				total = choice_to_depo + store_depo_bal;
				cout << "Your total remaining balance is: " << total << endl;
				int up_id, up_balance;
				ifstream update_balance("Balance.txt");
				ofstream tem("temp.txt", ios::out | ios::app);
				while(update_balance >> up_id >> up_balance)
				{
					if(store_u_id != up_id)
					{
						tem << up_id << " " << up_balance << endl;
					}
				}
					tem << store_u_id << " " << total << endl;
						
					update_balance.close(); tem.close(); 
			
					remove("Balance.txt");
					rename("temp.txt", "Balance.txt");
					
				cout << "Thank you for depositting" << endl;
				cout << "[1] Back" << endl;
				cout << "[2] Exit" << endl;
				cout << "Choice: " << endl;
				cin >> de_choice;
				while(de_choice != '1' && de_choice != '2')
				{
					cout << "Invalid Input! Please enter the correct choice!" << endl;
					cout << "Choice: ";
					cin >> de_choice;
				}
				switch(de_choice)
				{
					case '1': system("cls"); goto login_menu_again; break;
					case '2': system("pause"); exit(0); break;
				}
			}
			if(login_choice == '3')		
			{
				char bi_choice;
				int bal_id, bal_bal, store_bal;
				ifstream balance_balance("Balance.txt");
				while(balance_balance >> bal_id >> bal_bal)
				{
					if(bal_id == store_u_id)
					{
						store_bal = bal_bal;
					}
				}
				balance_balance.close();
				cout << "BALANCE INQUIRY" << endl;
				cout << "Your Remaining Balance is: " << store_bal << endl;
				cout << "[1] Back" << endl;
				cout << "[2] Exit" << endl;
				cout << "Choice: " << endl;
				cin >> bi_choice;
				while(bi_choice != '1' && bi_choice != '2')
				{
					cout << "Invalid Input! Please enter the correct choice!" << endl;
					cout << "Choice: ";
					cin >> bi_choice;
				}
				switch(bi_choice)
				{
					case '1': system("cls"); goto login_menu_again; break;
					case '2': system("pause"); exit(0); break;
				}
			}
					
			if(login_choice == '4') { system("pause"); exit(0); }
	}
	if(check != 1)
	{
		cout << "Incorrect Username and Password!" << endl;
	}
}

void login_menu()
{
	cout << "What do you want to do?" << endl;
	cout <<"[1] Withdrawal " << endl ;
	cout <<"[2] Deposit" << endl;
	cout <<"[3] Balance Inquiry" << endl;
	cout <<"[4] Exit" << endl;
	cout << "Choice: ";
}


