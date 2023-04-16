#ifndef VALIDATOR_H
# define VALIDATOR_H

# include "grid.h"

int		valid_no_repetition(t_grid grid, const unsigned int length,
			const t_point pos);
int		valid_view(t_grid grid, const unsigned int length,
			const int *arr_view, const t_point pos);
int		all_valid(t_grid grid, const unsigned int length, const int *arr_view);

#endif
