#include "PhoneBook.hpp"

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
		os << color;
	return color;
}

int print_color(std::string text, bool bold,bool endl, std::ostream &os)
{
	if (bold)
		os << ANSI_BOLD;
	get_color(os);
	os << text << ANSI_COLOR_RESET;
	fflush(stdout);
	if (endl)
		os << std::endl;
	return 1;
}

std::string str_to_upper(std::string str)
{
	for (size_t i = 0; i < str.size(); i++)
		str[i] = std::toupper(str[i]);
	return str;
}

std::string format(std::string str)
{
	if (str.length() > 10)
		str = str.substr(0, 9) + ".";
	int lim = 10 - str.length();
	for (int i = 0; i < lim; i++)
		str += " ";
	return str;;
}

int	main(void)
{
	PhoneBook	phonebook;

	std::string command;
	while (print_color("Enter a command ", true, false) && std::getline(std::cin, command))
	{
		command = str_to_upper(command);
		if (command == "ADD")
			phonebook.add_contact();
		else if (command == "SEARCH")
			phonebook.search_contact();
		if (command == "EXIT" || std::cin.eof())
			break;
	}
	if (command != "EXIT")
		std::cout << std::endl;
	print_color("Goodbye!", true, true);
}