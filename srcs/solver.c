#include "rush.h"	

void	*ft_memset(void *dst, const char set, const size_t bytes)
{
	char		*it;
	const char	*end = dst + bytes;

	it = dst;
	while (it != end)
		*it++ = set;
	return (dst);
}

static int	**grid_new(const unsigned int length)
{
	int					**grid;
	unsigned int		y;
	const unsigned int	line_bytes = length * sizeof(int);

	y = -1;
	grid = malloc(length * sizeof(int *));
	while (++y < length)
		grid[y] = ft_memset(malloc(line_bytes), 0, line_bytes);
	return (grid);
}

static void	grid_clear(int **grid, const unsigned int length)
{
	unsigned int	y;

	y = -1;
	while (++y < length)
		free(grid[y]);
	free(grid);
}

static void	ft_iatoa(char *str, const int *line, const unsigned int length)
{
	unsigned int	i;

	i = -1;
	while (++i < length)
		str[i] = line[i] + '0';
}

void	grid_dlog(const int fd, int **grid, const int length,
			const int *arr_view)
{
	int				y;
	char			*line;
	const size_t	line_length = length + 4;

	y = -1;
	line = ft_memset(malloc(line_length + 1), ' ', line_length);
	line[line_length] = '\0'; 
	ft_iatoa(&line[2], arr_view, length);
	ft_dputendl(fd, line);
	while (++y < length)
	{
		line[0] = arr_view[length * y] + '0';
		ft_iatoa(&line[2], grid[y], length);
		line[line_length - 1] = arr_view[length * (y + 1)] + '0';
		ft_dputendl(fd, line);
	}
	line[0] = ' ';
	line[line_length - 1] = ' ';
	ft_iatoa(&line[2], &arr_view[length * 3], length);
	ft_dputendl(fd, line);
	free(line);
}

int	solve(t_game game)
{
	return (0);
}

int	rush_solve(const int *arr_view, const unsigned int size)
{
	const t_game	game = {
		.grid.layout = grid_new(size / 4),
		.grid.length = size / 4,
		.arr_view = arr_view,
		.size = size
	};
	const int		status = solve(game);

	grid_dlog(2, game.grid.layout, game.grid.length, game.arr_view);
	grid_clear(game.grid.layout, game.grid.length);
	return (0);
}