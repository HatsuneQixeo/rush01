#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

int				ft_isdigit(int c);
void			ft_strskip(const char **p_str, const char c);
int				ft_stoi(const char *str, size_t *const pos);
void			*ft_memset(void *dst, const char set, const size_t bytes);

unsigned int	ft_dputchar(const int fd, const char c);
unsigned int	ft_dputnbr(const int fd, const int n);
unsigned int	ft_dputstr(const int fd, const char *str);
unsigned int	ft_dputendl(const int fd, const char *str);

#endif
