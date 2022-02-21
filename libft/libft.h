#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# define GNL_BUFF_SIZE 1024

int		ft_max(int a, int b);
int		ft_min(int a, int b);
int		ft_abs(int a);
double	ft_abs_double(double a);
int		ft_strlen(const char *str);
void	*ft_memset(void *str, int c, size_t len);
char	*ft_memcpy(char *dest, const char *src, int n);
char	*ft_strdup(const char *s);
void	ft_memfree(void **pointer);
void	ft_arrayfree(void ***array, size_t count);
int		ft_atoi(const char *str);
int		ft_gnl(int fd, char **line);
int		ft_split_count(char const *str, char c);
char	**ft_split(char const *s, char c);

#endif
