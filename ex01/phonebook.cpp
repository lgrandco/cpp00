#include <iostream>
#include <stdio.h>
#include "PhoneBook.hpp"

#include <string>

void PhoneBook::add_contact()
{
	Contact	contact;
	int idx;

	while (!std::cin.eof() && print_color(" ○ Enter first name ", true, false) && getline(std::cin, contact.first_name) && contact.first_name == "")
		std::cin.clear();
	while (!std::cin.eof() && print_color(" ○ Enter last name ", true, false) && getline(std::cin, contact.last_name) && contact.last_name == "")
		std::cin.clear();
	while (!std::cin.eof() && print_color(" ○ Enter nickname ", true, false) && getline(std::cin, contact.nickname) && contact.nickname == "")
		std::cin.clear();
	while (!std::cin.eof() && print_color(" ○ Enter phone name ", true, false) && getline(std::cin, contact.phone_number) && contact.phone_number == "")
		std::cin.clear();
	while (!std::cin.eof() && print_color(" ○ Enter darkest secret ", true, false) && getline(std::cin, contact.darkest_secret) && contact.darkest_secret == "")
		std::cin.clear();
	if (contacts_nb == 8)
	{
		idx = oldest_idx;
		oldest_idx = (oldest_idx + 1) % 8;
		print_color("Contact list is full, oldest contact has been overwritten", true, true);
	}
	else
		idx = contacts_nb++;
	contacts[idx] = contact;
}

void PhoneBook::search_contact()
{
	if (contacts_nb == 0)
	{
		print_color("No contacts",true, true, std::cerr);
		return;
	}
	std::cout << ANSI_BOLD;
	for (int i = 0; i++ < 45; std::cout << "-"){}
	std::cout << "\n|" << format("Index") << "|" << format ("First name") << "|" << format("Last name") << "|" << format("Nickname") << "|" << std::endl;
	for (int i = 0; i < contacts_nb; i++)
		std::cout << get_color() << "|" << i << "         " <<  "|" << format(contacts[i].first_name) << "|" << format(contacts[i].last_name) << "|" << format(contacts[i].nickname) << "|" << std::endl;
	std::cout << ANSI_COLOR_RESET << ANSI_BOLD;
	for (int i = 0; i++ < 45; std::cout << "-"){}
	size_t idx;
	std::string idx_str;
	while (!(print_color("\nEnter an index: ",true,false) && std::getline(std::cin, idx_str) && idx_str.size() == 1 && idx_str[0] >= '0' && idx_str[0] - '0' < contacts_nb) && !std::cin.eof())
		print_color("Invalid index",true, false, std::cerr);
	if (std::cin.eof())
		return;
	idx = idx_str[0] - '0';
	print_color(" • First name: " + contacts[idx].first_name, true, true);
	print_color(" • Last name: " + contacts[idx].last_name, true, true);
	print_color(" • Nickname: " + contacts[idx].nickname, true, true);
	print_color(" • Phone number: " + contacts[idx].phone_number, true, true);
	print_color(" • Darkest secret: " + contacts[idx].darkest_secret, true, true);
}
