#ifndef GRID_H
# define GRID_H

# include <stdbool.h>
# include "utils.h"
# include "point.h"


typedef struct s_tile
{
	int		value;
	bool	*arr_option;
}			t_tile;

void	option_show(const bool *arr_options, const unsigned int length);

typedef t_tile**	t_grid;

t_grid	grid_new(const unsigned int length);
void	grid_clear(t_grid grid, const unsigned int length);

void	grid_dlog(const int fd, t_grid grid, const unsigned int length,
			const int *arr_view);
void	grid_show_option(t_grid grid, const unsigned int length);

#endif
