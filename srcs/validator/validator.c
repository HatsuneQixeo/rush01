#include "grid.h"

static int	view_count(t_grid grid, const unsigned int length,
			const t_point start, const t_point dir)
{
	unsigned int	count;
	int				highest;
	t_point			it;

	count = 0;
	highest = 0;
	it = start;
	while (it.x < length && it.y < length)
	{
		if (grid[it.y][it.x].value > highest)
		{
			count++;
			highest = grid[it.y][it.x].value;
		}
		it = point_sum(it, dir);
	}
	return (count);
}

int	valid_view(t_grid grid, const unsigned int length,
			const int *arr_view, const t_point pos)
{
	const int	updown = view_count(grid, length,
				(t_point){.x = pos.x, .y = 0},
				(t_point){.x = 0, .y = 1})
				== arr_view[pos.x]
			&& view_count(grid, length,
				(t_point){.x = pos.x, .y = length - 1},
				(t_point){.x = 0, .y = -1})
				== arr_view[pos.x + length];
	const int	leftright = view_count(grid, length,
				(t_point){.x = 0, .y = pos.y},
				(t_point){.x = 1, .y = 0})
				== arr_view[pos.y + length * 2]
			&& view_count(grid, length,
				(t_point){.x = length - 1, .y = pos.y},
				(t_point){.x = -1, .y = 0})
				== arr_view[pos.y + length * 3];

	if (pos.x == length - 1 && pos.y == length - 1)
		return (updown && leftright);
	else if (pos.x == length - 1)
		return (leftright);
	else if (pos.y == length - 1)
		return (updown);
	else
		return (1);
}

int	all_valid(t_grid grid, const unsigned int length, const int *arr_view)
{
	unsigned int	i;

	i = -1;
	while (++i < length)
	{
		if (!valid_view(grid, length, arr_view,
				(t_point){.x = length - 1, .y = i})
			|| !valid_view(grid, length, arr_view,
				(t_point){.x = i, .y = length - 1}))
			return (0);
	}
	return (1);
}

int	valid_no_repetition(t_grid grid, const unsigned int length,
			const t_point pos)
{
	unsigned int	i;
	const int		value = grid[pos.y][pos.x].value;

	i = -1;
	while (++i < length)
	{
		if ((i != pos.y && grid[i][pos.x].value == value)
			|| (i != pos.x && grid[pos.y][i].value == value))
			return (0);
	}
	return (1);
}
