#include "rush.h"

/**
 * @brief 
 * Up = x
 * Down x + length
 * Left = y + (length * 2)
 * Right = y = (length * 3)
 */
int	option_only_one(t_grid grid, const unsigned int length, const t_point pos);

/*
	Set the given position as given value,
	and eliminate the option of the given value
	in the given row and column of the position

	Also clears all the rest of the option in the given position
*/
void	option_eliminate(t_grid grid, const unsigned int length,
			const t_point pos, const int value)
{
	unsigned int	i;
	const int		del = value - 1;

	// fprintf(stderr, "eliminate: %d ", value);
	// point_flog(stderr, "at: ", pos);
	grid[pos.y][pos.x].value = value;
	ft_memset(grid[pos.y][pos.x].arr_option, false, length);
	i = -1;
	while (++i < length)
	{
		const t_point	del_y = {
			.x = pos.x,
			.y = i
		};
		const t_point	del_x = {
			.x = i,
			.y = pos.y
		};

		grid[i][pos.x].arr_option[del] = false;
		option_only_one(grid, length, del_y);
		grid[pos.y][i].arr_option[del] = false;
		option_only_one(grid, length, del_x);
	}
}

/*
	Can't have a function to do this without creating another struct,
	too much parameter for norminette
*/
static bool	chosen_verification(t_grid grid, const unsigned int length,
			const t_point pos, const unsigned int i_option)
{
	t_point	it;

	it = (t_point){.x = -1, .y = -1};
	while (++it.y < length)
	{
		if (it.y != pos.y && grid[it.y][pos.x].arr_option[i_option] == true)
			break ;
	}
	if (it.y == length)
		return (true);
	while (++it.x < length)
	{
		if (it.x != pos.x && grid[pos.y][it.x].arr_option[i_option] == true)
			break ;
	}
	if (it.x == length)
		return (true);
	return (false);
}

/*
	Iterate through the option,
	return the index of the available option
	that is exclusive to either the row to column of given position

	return 0 if no option is exclusive to this cell
*/
/* n cube time complexity let's goo */
int	option_chosen_one(t_grid grid, const unsigned int length, const t_point pos)
{
	unsigned int	option;
	const bool		*arr_option = grid[pos.y][pos.x].arr_option;

	option = -1;
	while (++option < length)
	{
		if (arr_option[option] == true
			&& chosen_verification(grid, length, pos, option))
		{
			// point_flog(stderr, "chosen elimination: ", pos);
			option_eliminate(grid, length, pos, option + 1);
			return (option);
		}
	}
	return (0);
}

/* Not sure if it's a great idea letting this function do indirect recursion */
int	option_only_one(t_grid grid, const unsigned int length, const t_point pos)
{
	bool *const		arr_option = grid[pos.y][pos.x].arr_option;
	unsigned int	i;
	bool			*last_seen;

	i = -1;
	last_seen = NULL;
	while (++i < length)
	{
		if (arr_option[length] == true)
		{
			if (last_seen != NULL)
				return (0);
			last_seen = &arr_option[length];
		}
	}
	if (last_seen == NULL)
		return (0);
	// point_flog(stderr, "only elimination: ", pos);
	option_eliminate(grid, length, pos, (last_seen - arr_option) + 1);
	return (1);
}

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

/**
 * @brief 
 * 
 * 2 problem with this guy
 * 1:
 * 	This function can actually solve an invalid puzzle in it's own,
 * 	gonna need to call validator to make sure 
 * 2:
 * 	Filling in the cell beforehand seem to have some conflict with the solver,
 * 	causing the solver not backtrack properly
 * 	(likely has to do with validator not reporting error properly)
 * 	Fixed: It's because the control flow in the solver
 * 		caused it to skipped over the filled cell direcly without any checking,
 * 		meaning it skipped over the validator check
 * @param grid 
 * @param length 
 * @return int 
 */
int	elimination_fill(t_grid grid, const unsigned int length)
{
	t_point	it;
	int		doing;

	it.y = -1;
	doing = 0;
	while (++it.y < length)
	{
		it.x = -1;
		while (++it.x < length)
		{
			// point_flog(stderr, "it) ", it);
			// getchar();
			doing |= option_chosen_one(grid, length, it);
		}
	}
	return (doing);
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
		const int			view = arr_view[i];
		const t_point		dir = directions[i / length];
		const unsigned int	diff = (length - view) + 1;

		for (unsigned int eliminate = length; eliminate > diff; eliminate--)
		{
			t_point			it = grid_startpoint(length, i);
			unsigned int	reach = eliminate - diff;

			while (reach--)
			{
				grid[it.y][it.x].arr_option[eliminate - 1] = false;
				it = point_sum(it, dir);
			}
		}
	}
	// grid_show_option(grid, length);
	// grid_dlog(2, grid, length, arr_view);
	// getchar();
	while (elimination_fill(grid, length))
		// grid_dlog(2, grid, length, arr_view);
		;
	// grid_show_option(grid, length);
	// grid_dlog(2, grid, length, arr_view);
}
