#include "rush.h"

t_point	point_sum(const t_point a, const t_point b)
{
	t_point	point;

	point.x = a.x + b.x;
	point.y = a.y + b.y;
	return (point);
}

static int	view_count(int **grid, const unsigned int length,
			const t_point start, const t_point dir)
{
	unsigned int	count;
	int				largest;
	t_point			pos;

	count = 0;
	largest = 0;
	pos = start;
	while (pos.x < length && pos.y < length)
	{
		if (grid[pos.y][pos.x] > largest)
		{
			count++;
			largest = grid[pos.y][pos.x];
		}
		pos = point_sum(pos, dir);
	}
	return (count);
}

int	valid_view(int **grid, const unsigned int length,
			const int *arr_view, const t_point pos)
{
	const int	up = arr_view[pos.x];
	const int	down = arr_view[pos.x + length];
	const int	left = arr_view[pos.y + length * 2];
	const int	right = arr_view[pos.y + length * 3];

	return (view_count(grid, length,
			(t_point){.x = pos.x, .y = 0},
			(t_point){.x = 0, .y = 1})
			<= up
		&& view_count(grid, length,
			(t_point){.x = pos.x, .y = length - 1},
			(t_point){.x = 0, .y = -1})
			<= down
		&& view_count(grid, length,
			(t_point){.x = 0, .y = pos.y},
			(t_point){.x = 1, .y = 0})
			<= left
		&& view_count(grid, length,
			(t_point){.x = length - 1, .y = pos.y},
			(t_point){.x = -1, .y = 0})
			<= right);
}

int	valid_no_repetition(int **grid, const unsigned int length,
			const t_point pos)
{
	t_point		it;
	const int	value = grid[pos.y][pos.x];

	it = pos;
	while (++it.y % length != pos.y)
	{
		it.y %= length;
		if (grid[it.y][pos.x] == value)
			return (0);
	}
	while (++it.x % length != pos.x)
	{
		it.x %= length;
		if (grid[pos.y][it.x] == value)
			return (0);
	}
	return (1);
}
