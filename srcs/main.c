#include "rush.h"
#include "utils.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		ft_dputendl(2, "Error: Bad Arguments");
	else
	{
		const int	status = rush01(argv[1]);
		// system("leaks -q rush01.exe");
		return (status);
	}
	return (1);
}
