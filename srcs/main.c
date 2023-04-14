#include "rush.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		ft_dputendl(2, "Error: Bad Arguments");
	else
		return (rush01(argv[1]));
	return (1);
}
