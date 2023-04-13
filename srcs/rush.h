#ifndef RUSH_H
# define RUSH_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_grid
{
	int	**layout;
	int	length;
}			t_grid;

typedef struct s_point
{
	int	x;
	int	y;
}			t_point;

typedef struct s_game
{
	t_grid		grid;
	const int	*arr_view;
	int			size;
}			t_game;

size_t	ft_strlen(const char *str);
void	ft_dputendl(const int fd, const char *str);
int		ft_isdigit(int c);
void	ft_strskip(const char **p_str, const char c);
int		ft_stoi(const char *str, size_t *pos);

int		valid_no_repetition(t_grid grid, const t_point pos);
int		valid_view(t_grid grid, const int *arr_view, const t_point pos);

int		rush_solve(const int *arr_view, const unsigned int size);

#endif