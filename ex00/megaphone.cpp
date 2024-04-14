#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>

# define ANSI_COLOR_RED "\x1b[31m"
# define ANSI_COLOR_GREEN "\x1b[32m"
# define ANSI_COLOR_YELLOW "\x1b[33m"
# define ANSI_COLOR_BLUE "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN "\x1b[36m"
# define ANSI_WHITE "\x1b[37m"
# define ANSI_COLOR_RESET "\x1b[0m"
# define ANSI_BOLD "\x1b[1m"

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

int main(int argc, char const *argv[])
{
	get_color(std::cout);
	if (argc == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	for (size_t i = 1; argv[i]; i++)
		for (size_t j = 0; argv[i][j]; j++)
			std::cout << static_cast<char>(toupper(argv[i][j]));
	std::cout << std::endl;
	if (isatty(STDOUT_FILENO))
		std::cout << ANSI_COLOR_RESET;
	return 0;
}
