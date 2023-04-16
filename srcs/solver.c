#include "grid.h"	
#include "validator.h"
#include "eliminator.h"

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
		return (valid_view(grid, length, arr_view, pos)
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
