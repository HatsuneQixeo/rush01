#include "rush.h"

t_point	point_sum(const t_point a, const t_point b)
{
	t_point	point;

	point.x = a.x + b.x;
	point.y = a.y + b.y;
	return (point);
}

static int	view_count(t_grid grid, const t_point start, const t_point dir)
{
	unsigned int	count;
	int				prev;
	t_point			pos;

	count = 1;
	prev = grid.layout[start.y][start.x];
	pos = point_sum(start, dir);
	while (0 <= pos.x && pos.x < grid.length
		&& 0 <= pos.y && pos.y < grid.length
		&& grid.layout[pos.y][pos.x] > prev)
	{
		count++;
		prev = grid.layout[pos.y][pos.x];
		pos = point_sum(pos, dir);
	}
	return (count);
}

int	valid_view(t_grid grid, const int *arr_view, const t_point pos)
{
	const int	up = arr_view[pos.x];
	const int	down = arr_view[pos.x + grid.length];
	const int	left = arr_view[pos.y + grid.length * 2];
	const int	right = arr_view[pos.y + grid.length * 3];

	return (view_count(grid, (t_point){.x = pos.x, .y = 0},
				(t_point){.x = 0, .y = 1}) <= up
		&& view_count(grid, (t_point){.x = pos.x, .y = grid.length - 1},
				(t_point){.x = 0, .y = -1}) <= down
		&& view_count(grid, (t_point){.x = 0, .y = pos.y},
				(t_point){.x = 1, .y = 0}) <= left
		&& view_count(grid, (t_point){.x = grid.length - 1, .y = pos.y},
				(t_point){.x = -1, .y = 0}) <= right);
}

int	valid_no_repetition(t_grid grid, const t_point pos)
{
	t_point		it;
	const int	value = grid.layout[pos.y][pos.x];

	it = pos;
	while (++it.y % grid.length != pos.y)
		if (grid.layout[it.y][pos.x] == value)
			return (0);
	while (++it.x % grid.length != pos.x)
		if (grid.layout[pos.y][it.x] == value)
			return (0);
	return (1);
}
