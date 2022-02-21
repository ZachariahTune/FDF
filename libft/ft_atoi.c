#include "libft.h"

int	ft_atoi(const char *str)
{
	int			sign;
	long int	ret;

	sign = 1;
	ret = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str == '0')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		ret = ret * 10 + (*str - 48);
		str++;
	}
	return ((int)(ret * sign));
}
