#ifndef RUSH_H
# define RUSH_H

# include <stdlib.h>
# include <stdio.h>

typedef struct s_point
{
	unsigned int	x;
	unsigned int	y;
}			t_point;

/* Utilites */
size_t	ft_strlen(const char *str);
int		ft_isdigit(int c);
void	ft_strskip(const char **p_str, const char c);
int		ft_stoi(const char *str, size_t *pos);
void	*ft_memset(void *dst, const char set, const size_t bytes);

int		valid_no_repetition(int **grid, const unsigned int length,
			const t_point pos);
int		valid_view(int **grid, const unsigned int length,
			const int *arr_view, const t_point pos);

int		rush_solve(const int *arr_view, const unsigned int size);

/* Logging */
void	ft_dputendl(const int fd, const char *str);
void	grid_dlog(const int fd, int **grid, const unsigned int length,
			const int *arr_view);

#endif
