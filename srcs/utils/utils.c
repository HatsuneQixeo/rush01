#include "utils.h"

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

void	ft_strskip(const char **p_str, const char c)
{
	while (**p_str != '\0' && **p_str == c)
		(*p_str)++;
}

int	ft_stoi(const char *str, size_t *const pos)
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

void	*ft_memset(void *dst, const char set, const size_t bytes)
{
	char		*it;
	const char	*end = dst + bytes;

	it = dst;
	while (it != end)
		*it++ = set;
	return (dst);
}
