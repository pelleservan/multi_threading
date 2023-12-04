#include <cstdlib>
#include <iostream>
#include <thread>
#include <mutex>
#include <array>

class BankAccount
{
public:
    BankAccount(int id, int balance);
    virtual ~BankAccount();
    void lock();
    void unlock();
    void change(int amount);
    void transaction(BankAccount& account2, int amount);
    int getBalance() const;

private:
    int m_id;
    int m_balance;
    std::mutex m_mtx;
};

BankAccount::BankAccount(int id, int balance)
    : m_id(id),
    m_balance(balance)
{
}

BankAccount::~BankAccount()
{
}

void BankAccount::change(int amount)
{
    m_balance += amount;
}

void BankAccount::lock()
{
    m_mtx.lock();
}

void BankAccount::unlock()
{
    m_mtx.unlock();
}

int BankAccount::getBalance() const
{
    return m_balance;
}

void BankAccount::transaction(BankAccount& account2, int amount)
{
    if (m_id < account2.m_id)
    {
        lock();
        account2.lock();
    }
    else
    {
        account2.lock();
        lock();
    }

    change(-1 * amount);
    account2.change(amount);
    //std::cout << m_id << " " << m_balance << std::endl; 
    unlock();
    account2.unlock();
}

int main(int argc, char** argv)
{
    BankAccount alice(1, 100);
    BankAccount bob(2, 100);
    BankAccount christian(3, 100);
    BankAccount david(4, 100);

    std::array<std::thread, 4> transactions;
    transactions[0] = std::thread(&BankAccount::transaction, &alice,
        std::ref(bob), 50);
    transactions[1] = std::thread(&BankAccount::transaction, &bob,
        std::ref(alice), 130);
    transactions[2] = std::thread(&BankAccount::transaction, &christian,
        std::ref(alice), 70);
    transactions[3] = std::thread(&BankAccount::transaction, &david,
        std::ref(christian), 20);

    for (size_t i = 0; i < transactions.size(); i++)
    {
        transactions[i].join();
    }

    std::cout << "Alice " << alice.getBalance() << std::endl;
    std::cout << "Bob " << bob.getBalance() << std::endl;
    std::cout << "Christian " << christian.getBalance() << std::endl;
    std::cout << "David " << david.getBalance() << std::endl;

    return EXIT_SUCCESS;
}
