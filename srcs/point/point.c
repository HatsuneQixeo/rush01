#include "point.h"
#include <stdio.h>

t_point	point_sum(const t_point a, const t_point b)
{
	t_point	point;

	point.x = a.x + b.x;
	point.y = a.y + b.y;
	return (point);
}

void	point_flog(FILE *file, const char *prefix, const t_point point)
{
	fprintf(file, "%sx: %d, y: %d\n", prefix, point.x, point.y);
}
