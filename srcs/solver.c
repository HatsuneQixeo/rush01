#include "rush.h"	

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

static t_grid	grid_new(const unsigned int length)
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

static void	grid_clear(t_grid grid, const unsigned int length)
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

static int	solve(t_grid grid, const unsigned int length,
			const int *arr_view, const unsigned int index)
{
	unsigned int	n;
	const t_point	pos = {
		.x = index % length,
		.y = index / length
	};

	if (index == length * length)
		return (1);
	else if (grid[pos.y][pos.x].value != 0)
		return (valid_no_repetition(grid, length, pos)
			&& valid_view(grid, length, arr_view, pos)
		 	&& solve(grid, length, arr_view, index + 1));
	n = 0;
	while (n++ < length)
	{
		if (grid[pos.y][pos.x].arr_option[n - 1] == false)
			continue ;
		grid[pos.y][pos.x].value = n;
		if (valid_no_repetition(grid, length, pos)
			&& valid_view(grid, length, arr_view, pos)
			&& solve(grid, length, arr_view, index + 1))
			return (1);
	}
	grid[pos.y][pos.x].value = 0;
	return (0);
}

int	rush_solve(const int *arr_view, const unsigned int size)	
{
	const unsigned int	length = size / 4;
	const t_grid		grid = grid_new(length);
	int					status;

	eliminator(grid, length, arr_view);
	status = solve(grid, length, arr_view, 0);
	grid_dlog(1, grid, length, arr_view);
	if (status == 1 && !all_valid(grid, length, arr_view))
	{
		fprintf(stderr, "no it's not\n");
		status = 0;
	}
	grid_clear(grid, length);
	return (status);
}
