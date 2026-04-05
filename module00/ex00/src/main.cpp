#include <iostream>
#include "../includes/Account.hpp"
#include "../includes/Bank.hpp"

int main()
{
    Bank bank = Bank();

    // Créer des comptes
    bank.createAccount(1000U);
    bank.createAccount(500U);

    bank.addMoney(1, 2000.0f);
    bank.addMoney(2, 1000.0f);

    bank.withdrawMoney(1, 100.0f);

    bank.requestLoan(2, 100U);

    // Afficher l'état de la banque
    std::cout << bank << std::endl;

    return (0);
}