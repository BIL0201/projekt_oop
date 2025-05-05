#include <iostream>
#include<vector>


using std::cout;
using std::string;
using std::vector;


/*
inspirace pro projekt: abstraktní třída strategie a pretizeni metod
*/

class Client
{
    private:
    int code;
    string name;

    public:
    Client(int c, string n)
    {
        this->name = n;
        this->code = c;
    }

    int GetCode();
    string GetName();

};

string Client::GetName()
{
    return this->name;
}

int Client::GetCode()
{
    return this->code;
}

class Account
{
    private:
    int number;
    double balance;
    double interestRate;

    Client *owner;

    public:
    Account(int n, Client *c)
    {
        this->number = n;
        this->owner = c;
    }

    int GetNumber();
    double GetBalance();
    double GetInterestRate();
    Client *GetOwner();
    
    virtual bool CanWithdraw(double a);

    void Deposit(double a);
    bool Withdraw(double a);
    void AddInterest();
};

bool Account::CanWithdraw(double a)
{
    if (a > this->balance)
    {
        return false;
    }
    return true;
}

int Account::GetNumber()
{
    return this->number;
}

double Account::GetBalance()
{
    return this->balance;
}

double Account::GetInterestRate()
{
    return this->interestRate;
}

Client *Account::GetOwner()
{
    return this->owner;
}


void Account::Deposit(double a)
{
    this->balance += a;
}

bool Account::Withdraw(double a)
{
    if (Account::CanWithdraw(a))
    {
        this->balance -= a;
    }
    return true;
}

void Account::AddInterest()
{
    this->interestRate += 3;
}


class partnerAccount : public Account
{
private:
Client *partner;

public:
partnerAccount(Client *p, int n, Client *c): Account(n, c)
{
    this->partner = p;
}

Client *getPartner();
};


Client *partnerAccount::getPartner()
{
    return this->partner;
}

class CreditAccount : public Account
{
private:
double credit;

public:
CreditAccount(int cr, int n, Client *c): Account(n, c)
{
    this->credit = cr;
}

double GetCredit();
bool CanWithdraw(double a);
void Deposit(double a);
};

double CreditAccount::GetCredit()
{
    return this->credit;
}

bool CreditAccount::CanWithdraw(double a)
{

    if (a > this->credit)
    {
        return false;
    }
    return true;
}

void CreditAccount::Deposit(double a)
{
    this->credit += a;
}



class Bank
{
    private:
    Client** clients;
    int clientsCount;
    int maxclients;

    Account** accounts;
    int accountsCount;
    int maxaccounts;

    public:
    Bank(int c, int a)
    {
        this->maxclients = c;
        this->accountsCount = 0;
        this->clientsCount = 0;
        this->maxaccounts = a;
        this->clients = new Client*[maxclients];
        this->accounts = new Account*[maxaccounts];
    }
    ~Bank()
    {
        delete this->accounts;
        delete this->clients;
    }

    Client *GetClient(int c);
    Account *GetAccount(int n);

    Client *CreateClient(int c, string n);
    Account* CreateAccount(int n, Client *c);
    Account* CreatepartnerAccount(int n, Client *c, Client *p);
    CreditAccount* CreatecreditAccount(int cr, int n, Client *c);
    
    void AddInterest();
};

Client *Bank::GetClient(int c)
{
    cout << clients[c]->GetName() << "\n";
    cout << clients[c]-> GetCode() << "\n";
    return this->clients[c];
}

Account *Bank::GetAccount(int a)
{
    cout << accounts[a]->GetOwner()->GetName() << "\n";
    cout << accounts[a]->GetOwner()->GetCode() << "\n";
    return this->accounts[a];

}

Client *Bank::CreateClient(int c, string n)
{
    Client *newClient = new Client(c, n);
    clients[clientsCount] = newClient;
    this->clientsCount += 1;
    
    
    return newClient;
}

Account *Bank::CreateAccount(int n, Client *c)
{
    Account *newAccount = new Account(n, c);
    accounts[accountsCount] = newAccount;
    this->accountsCount += 1;
    return newAccount;
}

Account *Bank::CreatepartnerAccount(int n, Client *c, Client *p)
{
    partnerAccount *newpartnerAccount = new partnerAccount(p, n, c);
    accounts[accountsCount] = newpartnerAccount;
    this->accountsCount += 1;
    return newpartnerAccount;
}

CreditAccount *Bank::CreatecreditAccount(int cr, int n, Client *c)
{
    CreditAccount *newcreditAccount = new CreditAccount(cr, n, c);
    accounts[accountsCount] = newcreditAccount;
    this->accountsCount += 1;
    return newcreditAccount;
}


void Bank::AddInterest()
{
    
}

int main()
{
    int a = 400;
    Bank *bank = new Bank(4500, 4810);
    Client *client1 = bank->CreateClient(69, "Vlad");
    Client *client2 = bank->CreateClient(57, "Andrejko");
    CreditAccount *account1 = bank->CreatecreditAccount(0, 789, client1);
    Account *account2 = bank->CreateAccount(48769, client2);
    bank->CreatepartnerAccount(468, client1, client2);
    account2 = account1;
    
    // bank->GetClient(0);
    // bank->GetAccount(0);

    account1->Deposit(1500);
    cout << "account1" << "\n";
    cout << "Balance: " << account1->GetBalance() << "\n";
    cout << "Credit: " << account1->GetCredit() << "\n";

    if (account1->CanWithdraw(a))
    { 
        cout << "yes, can withdraw " << a << "\n";
    }
    else
    {
        cout << "no" << "\n";
    }
    
    cout << "-------------------------------" << "\n";

    account2->Deposit(1500);
    cout << "account2" << "\n";
    cout << "Balance: " << account2->GetBalance() << "\n";
    
    
    if (account2->CanWithdraw(400))
    { 
        cout << "yes, can withdraw " << a << "\n";
    }
    else
    {
        cout << "no" << "\n";
    }
    
    
    

    

    return 0;
}