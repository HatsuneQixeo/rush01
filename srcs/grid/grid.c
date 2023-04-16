#include "grid.h"

static t_tile	tile_new(const unsigned int length)
{
	t_tile	tile;

	tile.value = 0;
	tile.arr_option = malloc(length);
	if (tile.arr_option == NULL)
		return (tile);
	ft_memset(tile.arr_option, true, length);
	return (tile);
}

t_grid	grid_new(const unsigned int length)
{
	t_grid				grid;
	t_point				i;
	const unsigned int	line_bytes = length * sizeof(**grid);

	grid = malloc(length * sizeof(*grid));
	i.y = -1;
	while (++i.y < length)
	{
		grid[i.y] = malloc(line_bytes);
		i.x = -1;
		while (++i.x < length)
			grid[i.y][i.x] = tile_new(length);
	}
	return (grid);
}

void	grid_clear(t_grid grid, const unsigned int length)
{
	t_point	i;

	i.y = -1;
	while (++i.y < length)
	{
		i.x = -1;
		while (++i.x < length)
			free(grid[i.y][i.x].arr_option);
		free(grid[i.y]);
	}
	free(grid);
}
