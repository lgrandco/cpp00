#include "Account.hpp"
#include "ctime"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>

# define ANSI_COLOR_RED "\x1b[31m"
# define ANSI_COLOR_GREEN "\x1b[32m"
# define ANSI_COLOR_YELLOW "\x1b[33m"
# define ANSI_COLOR_BLUE "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN "\x1b[36m"
# define ANSI_WHITE "\x1b[37m"
# define ANSI_COLOR_RESET "\x1b[0m"
# define ANSI_BOLD "\x1b[1m"

int print_color(std::string text, bool bold = false, bool endl = true, std::ostream &os = std::cout);
std::string get_color(std::ostream &os = std::cout);

int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

Account::Account(int initial_deposit)
{
	_accountIndex = _nbAccounts++;
	_amount = initial_deposit;
	_totalAmount += _amount;
	_nbDeposits = 0;
	_nbWithdrawals = 0;
	get_color();
	_displayTimestamp();
	std::cout << " index:" << _accountIndex << ";amount:" << _amount << ";created" << std::endl;
}

void Account::_displayTimestamp()
{
	std::time_t t = std::time(0);
	std::tm *now = std::localtime(&t);
	std::cout << "[" << now->tm_year + 1900 << (now->tm_mon+1) / 10 << (now->tm_mon+1) % 10 << now->tm_mday / 10 << now->tm_mday % 10 << "_" << now->tm_hour / 10 << now->tm_hour % 10 << now->tm_min / 10 << now->tm_min % 10 << now->tm_sec / 10 << now->tm_sec % 10 << "]";
}

int Account::getNbAccounts(void)
{
	return _nbAccounts;
}

int Account::getTotalAmount(void)
{
	return _totalAmount;
}

int Account::getNbDeposits(void)
{
	return _totalNbDeposits;
}

int Account::getNbWithdrawals(void)
{
	return _totalNbWithdrawals;
}

void Account::displayAccountsInfos(void)
{
	get_color();
	_displayTimestamp();
	std::cout << " accounts:" << _nbAccounts << ";total:" << _totalAmount << ";deposits:" << _totalNbDeposits << ";withdrawals:" << _totalNbWithdrawals << std::endl;
}

void Account::makeDeposit(int deposit)
{
	get_color();
	_displayTimestamp();
	std::cout << " index:" << _accountIndex << ";p_amount:" << _amount << ";deposit:" << deposit;
	_amount += deposit;
	_totalAmount += deposit;
	_nbDeposits++;
	_totalNbDeposits++;
	std::cout << ";amount:" << _amount << ";nb_deposits:" << _nbDeposits << std::endl;
}

bool Account::makeWithdrawal(int withdrawal)
{
	get_color();
	_displayTimestamp();
	std::cout << " index:" << _accountIndex << ";p_amount:" << _amount << ";withdrawal:";
	if (_amount < withdrawal)
	{
		std::cout << "refused" << std::endl;
		return false;
	}
	_amount -= withdrawal;
	_totalAmount -= withdrawal;
	_nbWithdrawals++;
	_totalNbWithdrawals++;
	std::cout << withdrawal << ";amount:" << _amount << ";nb_withdrawals:" << _nbWithdrawals << std::endl;
	return true;
}

int Account::checkAmount(void) const
{
	return _amount;
}

void Account::displayStatus(void) const
{
	get_color();
	_displayTimestamp();
	std::cout << " index:" << _accountIndex << ";amount:" << _amount << ";deposits:" << _nbDeposits << ";withdrawals:" << _nbWithdrawals << std::endl;
}

Account::~Account(void)
{
	get_color();
	_displayTimestamp();
	std::cout << " index:" << _accountIndex << ";amount:" << _amount << ";closed" << std::endl;
	if (isatty(STDOUT_FILENO))
		std::cout << ANSI_COLOR_RESET;
}

const static std::string colors[7] = {ANSI_COLOR_RED, ANSI_COLOR_GREEN, ANSI_COLOR_YELLOW, ANSI_COLOR_BLUE, ANSI_COLOR_MAGENTA, ANSI_COLOR_CYAN, ANSI_WHITE};

std::string get_color(std::ostream &os)
{
	static bool first = true;
	if (first)
	{
		std::srand(time(NULL));
		first = false;
	}
	std::string color = colors[std::rand() % 7];
	if (isatty(STDOUT_FILENO))
		os << color << ANSI_BOLD;
	return color;
}

int print_color(std::string text, bool bold,bool endl, std::ostream &os)
{
	if (bold)
		os << ANSI_BOLD;
	get_color(os);
	os << text << ANSI_COLOR_RESET;
	if (endl)
		os << std::endl;
	return 1;
}