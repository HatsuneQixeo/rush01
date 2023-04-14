#include <unistd.h>
#include "rush.h"

void	ft_dputendl(const int fd, const char *str)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

static void	ft_iatoa(char *str, const int *line, const unsigned int length)
{
	unsigned int	i;

	i = -1;
	while (++i < length)
		str[i] = line[i] + '0';
}

void	grid_dlog(const int fd, int **grid, const unsigned int length,
			const int *arr_view)
{
	unsigned int	y;
	char			*line;
	const size_t	line_length = length + 4;

	y = -1;
	line = ft_memset(malloc(line_length + 1), ' ', line_length);
	line[line_length] = '\0'; 
	ft_iatoa(&line[2], arr_view, length);
	ft_dputendl(fd, line);
	while (++y < length)
	{
		line[0] = arr_view[(length * 2) + y] + '0';
		ft_iatoa(&line[2], grid[y], length);
		line[line_length - 1] = arr_view[(length * 3) + y] + '0';
		ft_dputendl(fd, line);
	}
	ft_memset(line, ' ', line_length);
	ft_iatoa(&line[2], &arr_view[length], length);
	ft_dputendl(fd, line);
	free(line);
}
