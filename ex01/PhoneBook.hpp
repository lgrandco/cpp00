#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "colors.hpp"

class PhoneBook
{
  private:
	Contact contacts[8];
	int contacts_nb;
	int oldest_idx;;
  public:
	PhoneBook() : contacts_nb(0), oldest_idx(0) {}
	void add_contact();
	void search_contact();
};

std::string format(std::string str);

#endif // !PHONEBOOK_HPP