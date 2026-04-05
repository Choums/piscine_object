#pragma once

#include <iostream>
#include <vector>
#include "../includes/Bank.hpp"

class Bank;

class Account
{
    public:
        const unsigned int& getId() const;
        const float& getBalance() const;
        
    private:
        Account(const unsigned int initialDeposit = 0U);
        ~Account();
        
        void setBalance(const float amount);
    
    	/**	Attributes	*/
        unsigned int    _id;
        float           _balance;
        
        static unsigned int _incrId;

        friend class Bank;

    public:
        friend std::ostream& operator << (std::ostream& p_os, const Account& p_account)
        {
            p_os << "[" << p_account._id << "] - [" << p_account._balance << "]";
            return (p_os);
        }
};