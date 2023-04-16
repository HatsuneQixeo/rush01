#include "eliminator.h"

static int	option_only_one(t_grid grid, const unsigned int length,
			const t_point pos);

/*
	Set the given position as given value,
	and eliminate the option of the given value
	in the given row and column of the position

	Also clears all the rest of the option in the given position
*/
static void	option_fill(t_grid grid, const unsigned int length,
			const t_point pos, const int value)
{
	unsigned int	i;
	const int		del = value - 1;

	// fprintf(stderr, "fill: %d ", value);
	// point_flog(stderr, "at: ", pos);
	grid[pos.y][pos.x].value = value;
	ft_memset(grid[pos.y][pos.x].arr_option, false, length);
	i = -1;
	while (++i < length)
	{
		grid[i][pos.x].arr_option[del] = false;
		option_only_one(grid, length, (t_point){.x = pos.x, .y = i});
		grid[pos.y][i].arr_option[del] = false;
		option_only_one(grid, length, (t_point){.x = i, .y = pos.y});
	}
}

static int	option_only_one(t_grid grid, const unsigned int length,
			const t_point pos)
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
	debug_option_fill("only fill: ", pos);
	option_fill(grid, length, pos, (last_seen - arr_option) + 1);
	return (1);
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
static int	option_chosen_one(t_grid grid, const unsigned int length,
			const t_point pos)
{
	unsigned int	option;
	const bool		*arr_option = grid[pos.y][pos.x].arr_option;

	option = -1;
	while (++option < length)
	{
		if (arr_option[option] == true
			&& chosen_verification(grid, length, pos, option))
		{
			debug_option_fill("chosen fill: ", pos);
			option_fill(grid, length, pos, option + 1);
			return (option);
		}
	}
	return (0);
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
	int		filling;

	it.y = -1;
	filling = 0;
	while (++it.y < length)
	{
		it.x = -1;
		while (++it.x < length)
			filling |= option_chosen_one(grid, length, it);
	}
	return (filling);
}
