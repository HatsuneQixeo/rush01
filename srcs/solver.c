#include "rush.h"	

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

int	solve(int **grid, const unsigned int length, const int *arr_view,
			const unsigned int index)
{
	unsigned int	i;
	const t_point	pos = {
		.x = index % length,
		.y = index / length
	};

	if (!(pos.x < length && pos.y < length))
		return (1);
	i = 0;
	while (i++ < length)
	{
		grid[pos.y][pos.x] = i;
		if (valid_no_repetition(grid, length, pos)
			&& valid_view(grid, length, arr_view, pos)
			&& solve(grid, length, arr_view, index + 1))
			return (1);
	}
	grid[pos.y][pos.x] = 0;
	return (0);
}

int	rush_solve(const int *arr_view, const unsigned int size)	
{
	const unsigned int	length = size / 4;
	int **const			grid = grid_new(length);
	const int			status = solve(grid, length, arr_view, 0);

	grid_dlog(2, grid, length, arr_view);
	grid_clear(grid, length);
	return (status);
}