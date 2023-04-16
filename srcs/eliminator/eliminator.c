#include "eliminator.h"

t_point	grid_startpoint(const unsigned int length, const unsigned int i)
{
	if (i < length)
		return ((t_point){.x = i, .y = 0});
	if (i < length * 2)
		return ((t_point){.x = i % length, .y = length - 1});
	if (i < length * 3)
		return ((t_point){.x = 0, .y = i % length});
	return ((t_point){.x = length - 1, .y = i % length});
}

void	elimination_view(t_grid grid, const unsigned int length,
			const t_point start, const t_point dir, const unsigned int diff)
{
	unsigned int	eliminate;

	eliminate = length;
	while (--eliminate > diff)
	{
		t_point			it = start;
		unsigned int	reach = eliminate - diff;

		while (reach--)
		{
			grid[it.y][it.x].arr_option[eliminate] = false;
			it = point_sum(it, dir);
		}
	}
}

void	eliminator(t_grid grid, const unsigned int length, const int *arr_view)
{
	const unsigned int	view_size = length * 4;
	const t_point		directions[] = {
		{.x = 00, .y = +1},
		{.x = 00, .y = -1},
		{.x = +1, .y = 00},
		{.x = -1, .y = 00},
	};
	unsigned int		i;

	i = -1;
	while (++i < view_size)
	{
		const t_point		dir = directions[i / length];
		const unsigned int	diff = (length - arr_view[i]);

		elimination_view(grid, length, grid_startpoint(length, i), dir, diff);
		// for (unsigned int eliminate = length; eliminate > diff; eliminate--)
		// {
		// 	t_point			it = grid_startpoint(length, i);
		// 	unsigned int	reach = eliminate - diff;

		// 	while (reach--)
		// 	{
		// 		grid[it.y][it.x].arr_option[eliminate - 1] = false;
		// 		it = point_sum(it, dir);
		// 	}
		// }
	}
	// grid_dlog(2, grid, length ,arr_view);
	// grid_show_option(grid, length);
	while (elimination_fill(grid, length))
	// 	grid_dlog(2, grid, length, arr_view);
		;
	grid_dlog(2, grid, length, arr_view);
}
