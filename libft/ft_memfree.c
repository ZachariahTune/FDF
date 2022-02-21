#include "libft.h"

void	ft_memfree(void **pointer)
{
	free(*pointer);
	*pointer = NULL;
}
