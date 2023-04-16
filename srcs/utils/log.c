#include <unistd.h>
#include "utils.h"

unsigned int	ft_dputchar(const int fd, const char c)
{
	return (write(fd, &c, 1));
}

static unsigned int	dputnbr_core(const int fd, const unsigned int n)
{
	if (n / 10)
		return (dputnbr_core(fd, n / 10) + ft_dputchar(fd, (n % 10) + '0'));
	else
		return (ft_dputchar(fd, n + '0'));
}

unsigned int	ft_dputnbr(const int fd, const int n)
{
	if (n < 0)
		return (ft_dputchar(fd, '-') + dputnbr_core(fd, (unsigned int)-n));
	else
		return (dputnbr_core(fd, n));
}

unsigned int	ft_dputstr(const int fd, const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (write(fd, str, len));
}

unsigned int	ft_dputendl(const int fd, const char *str)
{
	return (ft_dputstr(fd, str) + ft_dputchar(fd, '\n'));
}
