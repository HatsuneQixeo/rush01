#include "grid.h"

/* This way of logging probably won't work if the length is more than 9 */
/* How naive I was, thinking I was ever going to even reach 9 */
void	option_show(const bool *arr_options, const unsigned int length)
{
	char *const		str = malloc(length + 1);
	unsigned int	i;

	i = -1;
	str[length] = '\0';
	while (++i < length)
		str[i] = (char []){' ', (i + 1) + '0'}[arr_options[i]];
	ft_dputendl(2, str);
	free(str);
}

void	grid_show_option(t_grid grid, const unsigned int length)
{
	t_point	it;

	it.y = -1;
	while (++it.y < length)
	{
		it.x = -1;
		while (++it.x < length)
		{
			/* Forbidden */
			point_flog(stderr, "", it);
			option_show(grid[it.y][it.x].arr_option, length);
		}
	}
}
