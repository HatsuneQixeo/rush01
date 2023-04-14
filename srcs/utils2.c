#include <unistd.h>
#include <stdlib.h>

void	*ft_memset(void *dst, const char set, const size_t bytes)
{
	char		*it;
	const char	*end = dst + bytes;

	it = dst;
	while (it != end)
		*it++ = set;
	return (dst);
}
