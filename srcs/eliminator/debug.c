#include "grid.h"

#ifndef DEBUG_OPTION_FILL
# define DEBUG_OPTION_FILL	0
#endif

void	debug_option_fill(const char *type, const t_point pos)
{
	if (!DEBUG_OPTION_FILL)
		return ;
	point_flog(stderr, type, pos);
}
