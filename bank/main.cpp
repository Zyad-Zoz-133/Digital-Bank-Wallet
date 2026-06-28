#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <string>
#include <vector>
#include <windows.h>
#include <ctime>
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <conio.h>
#include <cstdlib>
#include <sstream>
using namespace std;

class user;
extern vector<user> account;
int search(const vector<user> &account, int target);
void save_account(const vector<user> &account);
int AdminID = 10;
string Admin_pass = "Admin!123";

void sleep(int ms, string word)
{
    std::cout << word;
    Sleep(ms);
}

void Clear_Screen()
{
    system("cls");
}

bool isPassTheSame(string pass, string n_pass)
{
    return (pass == n_pass);
}

string code(string t, int id)
{
    int limit= 5;
    string res = "";
    int value = id % 10;
    int shift = min(limit,value);
    if (shift == 0)
        shift = 1;
    for (int i = 0; i < int(t.length()); i++)
    {
        unsigned char c = t[i];
        char coded = ((c + shift) % 256);
        if (coded == ',')
            res += char(coded + 1);
        else
            res += coded;
    }
    return res;
}

class Bank
{
public:
    int id;

protected:
    string pass;
    string name;
    int status;
    double balance;

public:
    bool IsActive() const { return status == 1; }
    string get_name() const { return name; }
    double get_balance() const { return balance; }
    int get_id() const { return id; }
    string get_pass() const { return pass; }
    void disActive()
    {
        if (IsActive())
        {
            status = 0;
            cout << "Account is now Inactive";
        }
        else
        {
            status = 1;
            cout << "Account is now Active";
        }
    }

    void set_id(int id)
    {
        if (IsActive())
        {
            this->id = id;
            cout << "Successful change";
        }
        else
        {
            cout << "Sorry this account isn't active";
        }
    }

    void set_name(string name)
    {
        if (IsActive())
        {
            this->name = name;
            cout << "Successful change";
        }
        else
        {
            cout << "Sorry this account isn't active";
        }
    }
};

string EnterPass2()
{
    string pass = "";
    char ch;
    while (true)
    {
        ch = _getch();
        if (ch == 13)
            break;
        if (ch == 8)
        {
            if (pass.length() > 0)
            {
                pass.pop_back();
                cout << "\b \b";
            }
        }
        else
        {
            pass.push_back(ch);
            cout << "*";
        }
    }
    return pass;
}

class user : public Bank
{
public:
    string EnterPass()
    {
        string pass = "";
        char ch;
        while (true)
        {
            pass = "";
            while (true)
            {
                ch = _getch();
                if (ch == 13)
                    break;
                if (ch == 8)
                {
                    if (pass.length() > 0)
                    {
                        pass.pop_back();
                        cout << "\b \b";
                    }
                }
                else
                {
                    pass.push_back(ch);
                    cout << "*";
                }
            }
            if (IsStrong(pass))
                break;
            else
                cout << "\nYour password is weak\nenter password again : ";
        }
        return pass;
    }

    void deposit(double amount)
    {
        this->balance += amount;
        cout << "Successful deposit";
        cout << endl
             << "Your balance = " << balance;
    }

    void set_pass(string pass)
    {
        this->pass = pass;
        cout << "\nthe password had been changed successfully" << endl;
    }

    void withdraw(double amount)
    {

        if (amount <= get_balance())
        {
            this->balance -= amount;
            cout << "Successful withdraw";
            cout << endl
                 << "Your balance = " << balance;
            save_account(account);
            return;
        }
        else
        {
            cout << "your balance isn't enough .\n";
            cout << "press any key to go back:";
            _getch();
            sleep(500, "\nLoading....");
            Clear_Screen();
            return;
        }
    }

    user(int id, string name, string pass, double balance, int status)
    {
        this->id = id;
        this->name = name;
        this->pass = pass;
        this->balance = balance;
        this->status = status;
    }

    user(int id, string name, string pass, double balance)
    {
        this->id = id;
        this->name = name;
        this->pass = pass;
        this->balance = balance;
        this->status = 1; // active by default
    }

    user()
    {
        this->id = 0;
        this->name = "";
        this->pass = "";
        this->balance = 0.0;
        this->status = 1;
    }

    int Login(vector<user> &account)
    {

        sleep(1000, "Loading..");
        Clear_Screen();
        cout << "=====  welcome to login page  =====";
        cout << "\nEnter the ID : ";
        int i;
        cin >> i;
        int c_index = search(account, i);
        return c_index;
    }

    void display()
    {
        sleep(1000, "Loading....");
        Clear_Screen();
        cout << "=====  Account info  =====\n";
        cout << "ID: " << get_id() << endl;
        cout << "Name: " << get_name() << endl;
        cout << "Balance: " << fixed << setprecision(2) << get_balance() << endl;
        cout << "Status: " << (IsActive() ? "Active" : "Inactive") << endl;
    }

    bool IsStrong(string pass)
    {
        bool is_space = any_of(pass.begin(), pass.end(), ::isspace);
        bool is_length = false;
        bool is_upper = any_of(pass.begin(), pass.end(), ::isupper);
        bool is_lower = any_of(pass.begin(), pass.end(), ::islower);
        bool is_sp = any_of(pass.begin(), pass.end(), ::ispunct);
        bool is_num = any_of(pass.begin(), pass.end(), ::isdigit);
        if (pass.length() >= 8)
            is_length = true;

        return (is_length && is_upper && is_lower && is_sp && is_num && !is_space);
    }

    bool is_id_there(const vector<user> &account, int t)
    {
        return (search(account, t) != -1);
    }

    int Creat_ID(const vector<user> &account)
    {
        while (true)
        {
            int id = 10000 + rand() % 90000;
            if (!is_id_there(account, id))
            {
                return id;
            }
        }
    }

    void signup(vector<user> &account)
    {
        system("cls");
        cout << "=====  Welcome to sign up menu  =====\n";
        int id = Creat_ID(account);
        double b;
        string n, p;
        cout << "Enter your name : ";
        cin >> n;
        cout << "Enter your password : ";
        p = EnterPass();
        cout << endl
             << "Enter started balance : ";
        cin >> b;
        user temp(id, n, code(p, id), b);
        account.push_back(temp);
        cout << "Account created successfully with ID: " << id << endl;
        save_account(account);
        sort(account.begin(), account.end(), [](const Bank &a, const Bank &b)
             { return a.get_id() < b.get_id(); });
    }

    void change_password(user &t)
    {
        cout << "Enter your old password : ";
        string old_pass = EnterPass2();
        if (code(old_pass, t.get_id()) == t.get_pass())
        {
            cout << "\nEnter your new password:";
            string pass = EnterPass();
            t.set_pass(code(pass, id));
            save_account(account);
            cout << "\nPress any key to go to the main menu:";
            _getch();
            return;
        }
        else
        {
            cout << "\nYou can't change your password " << endl;
            cout << "\nPress any key to go to the main menu:";
            _getch();
            return;
        }
    }

    void changeAccountStatus()
    {
        if (IsActive())
        {
            status = 0;
            cout << "Account is now Inactive";
        }
        else
        {
            status = 1;
            cout << "Account is now Active";
        }
    }

    bool logout()
    {
        bool user_ = true;
        cout << "Are you sure you want to logout? (y/n): ";
        char confirm;
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y')
        {
            user_ = false;
            sleep(1500, "Logging out...");
            Clear_Screen();
        }
        else
        {
            sleep(1500, "Logout cancelled. Returning to user menu.\n");
            Clear_Screen();
            user_ = true;
        }
        return user_;
    }

    bool logedin(vector<user> &account, int index)
    {

        if (index == -1)
        {
            cout << "Enter The password : ";
            string p = EnterPass2();
            cout <<endl <<"Invalid ID or password";
            cout << "Press any key to go to the main menu:";
            return false;
        }
        user &t = account[index];

        int tries = 3;
        string p;
        cout << "Enter The password : ";
        p = EnterPass2();
        while (tries > 0)
        {

            if (isPassTheSame(t.get_pass(), code(p, t.get_id())))
            {
                if (!t.IsActive())
                {
                    cout << "\nSorry, this account is Inactive.\n";
                    cout << "Press any key to go to the main menu:";
                    return false;
                }
                return true;
            }
            else
            {
                cout << "\nThe password is wrong (Tries left: " << tries << "): ";
                p = EnterPass2();
                tries--;
            }
            if(tries==0){
            cout << "\n\nYou entered the wrong password 3 times . Account has been locked.\n";
            t.disActive();
            save_account(account);
            Sleep(2000);
            return false;
            }
        }
    }

    void Menu(vector<user> &account, int index)
    {
        bool user_ = true;
        Clear_Screen();
        int x;
        while (user_)
        {
            user &t = account[index];
            sleep(750, "Loading....");
            Clear_Screen();
            cout << "=========================================" << endl;
            cout << "====      Welcome " << t.get_name() << " to the menu   ====" << endl;
            cout << "=========================================" << endl;
            cout << "Please choose from the following options : ";
            cout << "\n1. Deposit " << endl;
            cout << "2. Withdraw " << endl;
            cout << "3. Inactive Account " << endl;
            cout << "4. Display Account info " << endl;
            cout << "5. Change password " << endl;
            cout << "6. Logout " << endl;
            cout << "Enter Your choice : ";
            cin >> x;

            switch (x)
            {

            case 1:
            {
                sleep(750, "Loading....");
                Clear_Screen();
                double a;
                cout << "Enter the amount\n :";
                cin >> a;
                t.deposit(a);
                save_account(account);
                cout << endl
                     << "Press any key to go to the main menu:";
                sleep(1000, "loading....");
            }
            break;

            case 2:
            {
                double a;
                sleep(1000, "Loading....");
                Clear_Screen();
                cout << "======  Withdraw  ======";
                cout << "\nEnter the amount :";
                cin >> a;
                t.withdraw(a);
            }
            break;
            case 3:
            {
                cout << "Enter your password to Inactive your Account: ";
                string p = EnterPass2();
                if (t.get_pass() == code(p, t.get_id()))
                {
                    t.disActive();
                    cout << "\nyour Account disActivated successfully.\n";
                    user_ = false;
                    sleep(1500, "Logging out...");
                    Clear_Screen();
                    save_account(account);
                    break;
                }
                else
                {
                    cout << "\nWrong password. Returning to user menu.\n";
                    sleep(1500, "Loading....");
                    Clear_Screen();
                }
                break;
            }
            break;
            case 4:
            {
                cout << endl;
                t.display();
                cout << "\nPress any key to go to main menu : ";
                _getch();
                break;
            }
            case 5:
            {
                sleep(750, "Loading....");
                Clear_Screen();
                change_password(t);
                save_account(account);
                break;
            }
            case 6:
            {
                cout << "Are you sure you want to logout? (y/n): ";
                char confirm;
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y')
                {
                    user_ = false;
                    cout << "Logging out...";
                    Sleep(1500);
                    Clear_Screen();
                    return;
                }
                else
                {
                    cout << "Logout cancelled. Returning to user menu.\n";
                    cout << "Loading....";
                    sleep(1500, "Loading....");
                    Clear_Screen();
                }
            }
            default:
                cout << "invalid input";
                break;
            }
        }
    }
};
void save_account(const vector<user> &account);

void load_account(vector<user> &account)
{
    ifstream infile("account.txt");
    if (!infile)
        return;
    string line;
    string t_name, t_pass;
    while (getline(infile, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        string id_s, bal_s, stat_s;
        getline(ss, id_s, ',');
        getline(ss, t_name, ',');
        getline(ss, bal_s, ',');
        getline(ss, t_pass, ',');
        getline(ss, stat_s, ',');

        if (!id_s.empty())
        {
            user temp(stoi(id_s), t_name, t_pass, stod(bal_s), stoi(stat_s));
            account.push_back(temp);
        }
    }
}

vector<user> account;

void save_account(const vector<user> &account)
{
    ofstream outfile("account.txt");
    if (!outfile)
    {
        cout << "Error: Could not open file for saving!" << endl;
        return;
    }

    for (const auto &acc : account)
    {
        outfile << acc.get_id() << ","
                << acc.get_name() << ","
                << acc.get_balance() << ","
                << acc.get_pass() << ","
                << (acc.IsActive() ? 1 : 0) << endl;
    }

    outfile.close();
}

class Admin : public Bank
{

public:
    bool islogin;
    Admin(int id, string name, string pass)
    {
        islogin = false;
        this->id = id;
        this->name = name;
        this->pass = pass;
    }
    void display(const vector<user> &account)
    {
        system("cls");
        double totalBankMoney = 0;
        cout << left << setw(10) << "ID" << "| " << setw(20) << "Name" << "| " << setw(14) << "Balance" << "| " << setw(12) << "Status" << endl;
        for (const auto &acc : account)
        {
            cout << left << setw(10) << acc.get_id()
                 << "| " << setw(20) << acc.get_name()
                 << "| " << setw(14) << fixed << setprecision(2) << acc.get_balance()
                 << "| " << (acc.IsActive() ? "Active" : "Inactive") << endl;
            totalBankMoney += acc.get_balance();
        }
        cout << "\nTotal balance in the bank: " << fixed << setprecision(2) << totalBankMoney << endl;
    }

    bool Login(int _id, string pass)
    {
        Sleep(1000);
        system("cls");
        cout << "=====  welcome to Admin login page  =====";
        int i;
        cout << "\nEnter the ID : ";
        cin >> i;
        cout << "Enter The password : ";
        string p = EnterPass2();
        if (isPassTheSame(p, pass) && isPassTheSame(to_string(i), to_string(_id)))
        {
            islogin = true;
            cout << "\nLogin successful. Welcome, ";
            return true;
        }
        else
        {
            cout << "\nWrong data!";
            cout << endl
                 << "Press any key to go to the main menu:";
            _getch();
            return false;
        }
    }

    void Menu()
    {
        if (!islogin)
            return;

        Sleep(1000);
        system("cls");

        while (true)
        {
            Clear_Screen();
            int x;
            cout << "===================================" << endl;
            cout << "=====  welcome to Admin menu  =====" << endl;
            cout << "===================================" << endl
                 << endl;
            cout << "Please choose from the following options : ";
            cout << "\n1. Display All Accounts " << endl;
            cout << "2. Search For Account (ID)" << endl;
            cout << "3. change  Account status (ID)" << endl;
            cout << "4. Exit " << endl;
            cout << "Enter Your choice : ";
            cin >> x;
            sleep(1000, "Loading..");

            switch (x)
            {
            case 1:
            {
                display(account);
                cout << endl;
                cout << "press any key to go back : ";
                _getch();
                break;
            }

            case 2:
            {
                int D;
                Clear_Screen();
                cout << "=====  Search For Account  =====\n";
                cout << "Enter the ID : ";
                cin >> D;
                cout << "\nSearching....";
                Sleep(1000);
                sort(account.begin(), account.end(), [](const user &a, const user &b)
                     { return a.get_id() < b.get_id(); });
                int index = search(account, D);
                if (index == -1)
                {
                    cout << "this account doesn't found in the system ";
                    cout << endl
                         << "press any key to go back : ";
                    _getch();
                    break;
                }
                user &b = account[index];
                Clear_Screen();
                b.display();
                cout << "press * to change this Account status to " << (b.IsActive() ? "(InActive)" : "(Active)") << " or any other key to exit :";
                char x_choice;
                cin >> x_choice;
                cin.ignore();
                if (x_choice == '*')
                {
                    cout << "Are you sure you want to do this process ? [y/n] : ";
                    char y;
                    cin >> y;
                    if (y == 'y' || y == 'Y')
                    {
                        b.disActive();
                        cout << "done " << (b.IsActive() ? "(unActivated)" : "(Activated)") << " account " << endl;
                        save_account(account);
                        cout << "press any key to go back :";
                        _getch();
                        cout << "\nLoading....";
                        Sleep(1500);
                    }
                }
                else
                {
                    cout << "invalid input press any key to go back : ";
                    _getch();
                }
                break;
            }

            case 3:
            {

                Clear_Screen();
                cout << "Enter the ID of the account : ";
                int h;
                cin >> h;
                int index = search(account, h);
                if (index != -1)
                {
                    user &b = account[index];
                    cout << "Are you sure you want to " << (b.IsActive() ? "unActive" : "Active") << "? [y/n] : ";
                    char y;
                    cin >> y;
                    if (y == 'y' || y == 'Y')
                    {
                        b.disActive();
                        cout << "done " << (b.IsActive() ? "(Activated)" : "(unActivated)") << " account " << endl;
                        save_account(account);
                        cout << "press any key to go back :";
                        _getch();
                        Sleep(1000);
                    }
                    else
                    {
                        cout << "\ninvalid input press any key to go back : ";
                        _getch();
                    }
                }
                else
                {
                    cout << "this account not found in the system";
                    cout << "\npress any key to go back";
                    _getch();
                    Sleep(750);
                }
                break;
            }

            case 4:
            {
                cout << "\nExiting Admin Menu....";
                Sleep(1000);
                Clear_Screen();
                return;
            }

            default:
                cout << "\ninvalid input. Press any key to try again.";
                _getch();
                break;
            }
        }
    }
};

int mainMenu()
{
    int x;
    Clear_Screen();
    cout << "===================================" << endl;
    cout << "=====   Welcome to main menu   ====" << endl;
    cout << "===================================" << endl;
    cout << "Please choose from the following options : " << endl;
    cout << "1. Sign up " << endl;
    cout << "2. Login " << endl;
    cout << "3. Login As Admin " << endl;
    cout << "4. Exit " << endl;
    cout << "Enter Your choice : ";
    cin >> x;
    return x;
}

void run_the_wallet()
{
    bool running = true;
    Clear_Screen();
    while (running)
    {
        int choice = mainMenu();

        switch (choice)
        {
        case 1:
        {
            sleep(750, "Loading....");
            user temp;
            temp.signup(account);
            cout << "Press any key to go to the main menu: ";
            _getch();
            break;
        }
        case 2: // User Login
        {
            user temp;
            int index = temp.Login(account);
            bool is_user = temp.logedin(account, index);
            if (is_user)
            {
                temp.Menu(account, index);
            }
            else
            {
                _getch();
            }
            break;
        }
        case 3:
        {
            sleep(750, "Loading....");
            Admin admin_obj(AdminID, "Admin", Admin_pass);
            if (admin_obj.Login(AdminID, Admin_pass))
            {
                admin_obj.Menu();
            }
            break;
        }
        case 4:
        {
            Clear_Screen();
            cout << "Saving database... Goodbye!\n";
            save_account(account);
            Sleep(1000);
            running = false;
            break;
        }
        default:
        {
            cout << "\n Invalid input.";
            cout << "\n Press any key to try again :";
            _getch();
            break;
        }
        }
    }
}

int main()
{
    srand(time(0));
    load_account(account);
    sort(account.begin(), account.end(), [](const Bank &a, const Bank &b)
         { return a.get_id() < b.get_id(); });
    run_the_wallet();
    // TODO : Add a transfer money from one account to another account function and add it to the user menu and notification to the user when he receive money in his account
    return 0;
}

int search(const vector<user> &account, int target)
{
    int left = 0, right = account.size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (account[mid].id == target)
            return mid;
        if (target < account[mid].id)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}
