#ifndef ELIMINATOR_H
# define ELIMINATOR_H

# include "grid.h"

int		elimination_fill(t_grid grid, const unsigned int length);
void	eliminator(t_grid grid, const unsigned int length, const int *arr_view);

/* Debug */
void	debug_option_fill(const char *type, const t_point pos);

#endif
