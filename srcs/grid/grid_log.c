#include "grid.h"

static int	get_tilevalue(const unsigned int i, const void *arr)
{
	const t_tile	*line = arr;

	return (line[i].value);
}

static int	get_intvalue(const unsigned int i, const void *arr)
{
	const int	*line = arr;

	return (line[i]);
}

typedef int	(*t_get)(const unsigned int i, const void *arr);

static void	ft_iatoa(char *str, const void *line, const unsigned int length,
			t_get ft_get)
{
	unsigned int	i;

	i = -1;
	while (++i < length)
	{
		str[i * 2] = ft_get(i, line) + '0';
		str[(i * 2) + 1] = ' ';
	}
}

void	grid_dlog(const int fd, t_grid grid, const unsigned int length,
			const int *arr_view)
{
	unsigned int	y;
	char			*line;
	const size_t	line_length = length + (length - 1) + 4;

	line = ft_memset(malloc(line_length + 1), ' ', line_length);
	line[line_length] = '\0'; 
	ft_iatoa(&line[2], arr_view, length, get_intvalue);
	ft_dputendl(fd, line);
	y = -1;
	while (++y < length)
	{
		line[0] = arr_view[(length * 2) + y] + '0';
		ft_iatoa(&line[2], grid[y], length, get_tilevalue);
		line[line_length - 1] = arr_view[(length * 3) + y] + '0';
		ft_dputendl(fd, line);
	}
	ft_memset(line, ' ', line_length);
	ft_iatoa(&line[2], &arr_view[length], length, get_intvalue);
	ft_dputendl(fd, line);
	free(line);
}
