#include "rush.h"	

static int	**grid_new(const unsigned int length)
{
	int				**grid;
	unsigned int	y;
	unsigned int	x;

	y = -1;
	grid = malloc(length * sizeof(int *));
	while (++y < length)
	{
		grid[y] = malloc(length * sizeof(int));
		x = -1;
		while (++x < length)
			grid[y][x] = 0;
	}
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

	grid_clear(game.grid.layout, game.grid.length);
	return (0);
}