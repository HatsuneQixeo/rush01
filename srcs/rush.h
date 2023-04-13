#ifndef RUSH_H
# define RUSH_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

size_t	ft_strlen(const char *str);
void	ft_dputendl(const int fd, const char *str);
int		ft_isdigit(int c);
void	ft_strskip(const char **p_str, const char c);
int		ft_stoi(const char *str, size_t *pos);

#endif