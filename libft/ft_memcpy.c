#include "libft.h"

char	*ft_memcpy(char *dest, const char *src, int n)
{
	int	i;

	if ((dest == src) || n == 0)
		return (dest);
	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		(dest)[i] = (src)[i];
		i++;
	}
	return (dest);
}
