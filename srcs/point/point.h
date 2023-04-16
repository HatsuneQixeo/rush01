#ifndef POINT_H
# define POINT_H

# include <stdio.h>

typedef struct s_point
{
	unsigned int	x;
	unsigned int	y;
}			t_point;

t_point	point_sum(const t_point a, const t_point b);
void	point_flog(FILE *file, const char *prefix, const t_point point);

#endif
