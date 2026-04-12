#include "../includes/Account.hpp"

unsigned int Account::_incrId = 0U;

Account::Account(const unsigned int initialDeposit) :  _balance(initialDeposit) {
    _id = ++_incrId;
}

const unsigned int& Account::getId() const {
    return (this->_id);
}

void Account::setBalance(const float amount) {
    this->_balance += amount;
}

const float& Account::getBalance() const {
    return (this->_balance);
}