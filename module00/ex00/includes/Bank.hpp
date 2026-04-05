#pragma once

#include <algorithm>
#include "../includes/Account.hpp"

class Account;

class Bank {
	public:
		Bank();
		~Bank();

		void createAccount(const unsigned int initialDeposit);
		void deleteAccount(const unsigned int accountId);

		void requestLoan(const unsigned int accountId, const unsigned int amount);

		void addMoney(const unsigned int accountId, const float deposit);
		void withdrawMoney(const unsigned int accountId, const float requestedSum);

		
	private:
		Account*	getAccount(const unsigned int id);
		void		setLiquidity(const float amount);

		/**	Attributes	*/
		float _liquidity;
		std::vector<Account *> _clientAccounts;

	public:
		friend std::ostream& operator << (std::ostream& p_os, const Bank& p_bank)
		{
			p_os << "Bank informations : " << std::endl;
			p_os << "Liquidity : " << p_bank._liquidity << std::endl;
			for (size_t i(0); i < p_bank._clientAccounts.size(); i++)
				p_os << &(p_bank._clientAccounts[i]) << std::endl;
			// for (std::vector<Account*>::const_iterator it = p_bank._clientAccounts.begin(); it != p_bank._clientAccounts.end(); it++)
			// 	p_os << *(it) << std::endl;
			return (p_os);
		}
};