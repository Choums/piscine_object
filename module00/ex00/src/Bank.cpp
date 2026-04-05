#include "../includes/Bank.hpp"

Bank::Bank() : _liquidity(0.0f) {
	
}

Bank::~Bank() {
	for (std::vector<Account*>::iterator it = _clientAccounts.begin(); it != _clientAccounts.end(); it++)
		delete *it;
	_clientAccounts.clear();
}

void Bank::createAccount(const unsigned int initialDeposit)
{
	Account* newClient = new Account(initialDeposit);
	_clientAccounts.push_back(newClient);

	std::cout << "The account has been successfully opened with ID " << newClient->getId() << std::endl;
}

void Bank::deleteAccount(const unsigned int accountId) {
	std::vector<Account *>::iterator it = std::find_if(_clientAccounts.begin(), _clientAccounts.end(),
							[accountId](Account* account) { return (account->getId() == accountId); });

	if (it != _clientAccounts.end()) {
		const unsigned int id = (*it)->getId();
		delete *it;
		_clientAccounts.erase(it);
		std::cout << "The account " << id << " has been successfully closed" << std::endl;
	} else {
		std::cerr << "Account " << accountId << " does not exist!" << std::endl;
	}
}

void Bank::setLiquidity(const float amount) {
	this->_liquidity += amount;
}

void Bank::requestLoan(const unsigned int accountId, const unsigned int amount) {
	Account* client = getAccount(accountId);
	if (!client) {
		std::cerr << "client " << accountId << " does not exist ! " << std::endl;
		return ;
	}

	if (amount > this->_liquidity) {
		std::cerr << "The loan has been refused, the bank liquidity is insuficient ! " << std::endl;
		return ;
	}

	client->setBalance(static_cast<float>(amount));
	this->setLiquidity((static_cast<float>(amount) * -1.0f));
}


void Bank::addMoney(const unsigned int accountId, const float deposit) {

	Account* client = getAccount(accountId);
	if (!client) {
		std::cerr << "client " << accountId << " does not exist ! " << std::endl;
		return ;
	}

	const float interest = (deposit * 0.05f);
	setLiquidity(interest);

	std::cout << "The bank takes 5\% interest [" << interest << "]" << std::endl;

	client->setBalance(deposit - interest);
}

void Bank::withdrawMoney(const unsigned int accountId, const float requestedSum) {

	Account* client = getAccount(accountId);
	if (!client) {
		std::cerr << "client " << accountId << " does not exist ! " << std::endl;
		return ;
	}

	if (requestedSum > client->getBalance()) {
		std::cerr << "The withdraw has been refused, the balance is insuficient ! " << std::endl;
		return ;
	} else if (requestedSum <= 0.0f) {
		std::cerr << "The requested amount must be positive !" << std::endl;
		return ;
	}

	client->setBalance(requestedSum * -1.0f);
}

Account* Bank::getAccount(const unsigned int id) {
	std::vector<Account *>::iterator it = std::find_if(_clientAccounts.begin(), _clientAccounts.end(),
							[id](Account* account) { return (account->getId() == id); });
	return ((it != _clientAccounts.end() ? *it : NULL));
	
}