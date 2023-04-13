#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_dputendl(const int fd, const char *str)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

void	ft_strskip(const char **p_str, const char c)
{
	while (**p_str == c)
		(*p_str)++;
}

int	ft_stoi(const char *str, size_t *pos)
{
	int	value;

	if (str[*pos] == '-')
	{
		++*pos;
		return (-ft_stoi(str, pos));
	}
	else if (str[*pos] == '+')
		++*pos;
	value = 0;
	while (ft_isdigit(str[*pos]))
		value = (value * 10) + (str[(*pos)++] - '0');
	return (value);
}
