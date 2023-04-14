#include "rush.h"	

static char	*new_possibility(const unsigned int length)
{
	char	*arr_possible;
	size_t	i;

	arr_possible = malloc(length + 1);
	if (arr_possible == NULL)
		return (NULL);
	arr_possible[length] = '\0';
	i = -1;
	while (++i < length)
		arr_possible[i] = (i + 1) + '0';
	return (arr_possible);
}

static t_tile	**grid_new(const unsigned int length)
{
	t_tile				**grid;
	t_point				i;
	const unsigned int	line_bytes = length * sizeof(**grid);

	grid = malloc(length * sizeof(*grid));
	i.y = -1;
	while (++i.y < length)
	{
		grid[i.y] = malloc(line_bytes);
		i.x = -1;
		while (++i.x < length)
		{
			grid[i.y][i.x].value = 0;
			grid[i.y][i.x].arr_possible = new_possibility(length);
		}
	}
	return (grid);
}

static void	grid_clear(t_tile **grid, const unsigned int length)
{
	t_point	i;

	i.y = -1;
	while (++i.y < length)
	{
		i.x = -1;
		while (++i.x < length)
			free(grid[i.y][i.x].arr_possible);
		free(grid[i.y]);
	}
	free(grid);
}

static int	solve(t_tile **grid, const unsigned int length,
			const int *arr_view, const unsigned int index)
{
	unsigned int	n;
	const t_point	pos = {
		.x = index % length,
		.y = index / length
	};

	if (!(pos.x < length && pos.y < length))
		return (1);
	n = 0;
	while (n++ < length)
	{
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
	t_tile **const		grid = grid_new(length);
	// grid_dlog(1, grid, length, arr_view);
	const int			status = solve(grid, length, arr_view, 0);

	grid_dlog(1, grid, length, arr_view);
	grid_clear(grid, length);
	return (status);
}
