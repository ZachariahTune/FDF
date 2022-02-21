#include "fdf.h"

//Открытие файла карты
void	fdf_open_mapfile(int argc, char *filename, int *fd1, int *fd2)
{
	if (argc < 2)
		ft_puterror(1);
	if (argc > 2)
		ft_puterror(2);
	*fd1 = open(filename, O_RDONLY);
	*fd2 = open(filename, O_RDONLY);
	if (*fd1 < 0 || *fd2 < 0)
		ft_puterror(3);
}

//Инициализация структуры карты
t_map 	*fdf_map_init(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (map == NULL)
		ft_puterror(4);
	map->size_x = 0;
	map->size_y = 0;
	map->size_z = 0;
	map->xyz = NULL;
	map->color = 1;
	map->zscale = 1.0;
	map->zoom = 0.0;
	map->zoom_orig = 0.0;
	map->oxy = FDF_PI / 180 * 35;
	map->oxz = 0;
	map->oyz = FDF_PI / 180 * 50;
	map->pers = 0.0;
	map->mouse_press = 0;
	map->mlx = NULL;
	return (map);
}

//Количество строк файла карты
int		fdf_preread_map(int fd, t_map *map)
{
	int		lines;
	char	file_buf[1];

	lines = 0;
	file_buf[0] = '\0';
	while (read(fd, file_buf, 1) > 0)
	{
		if (file_buf[0] == '\n')
			lines++;
	}
	if (file_buf[0] != '\0' && file_buf[0] != '\n')
		lines++;
	if (lines > 0)
		map->xyz = (int **)malloc(sizeof(int **) * lines);
	if (lines == 0 || map->xyz == NULL)
	{
		ft_memfree((void **)&map);
		ft_puterror(5);
	}
	return (lines);
}

//Наполнение массива карты из массива строки
static int	fdf_map_fill(t_map *map, int line_i, char **split_a, int split_c)
{
	int			i;
	static int	split_c_tmp;

	if (split_c_tmp && split_c_tmp != split_c)
		return (0);
	map->xyz[line_i] = (int *)malloc(sizeof(int *) * split_c);
	if (map->xyz[line_i] == NULL)
		return (0);
	i = 0;
	while (i < split_c)
	{
		map->xyz[line_i][i] = ft_atoi(split_a[i]);
		i++;
	}
	split_c_tmp = split_c;
	return (1);
}

//Считывание строк карты
int		fdf_read_map(int fd, t_map *map, int line_i, int split_c)
{
	char	*line;
	char	**split_a;

	split_a = NULL;
	while (ft_gnl(fd, &line) >= 0 && line[0] != '\0' && map->size_y > 1)
	{
		split_c = ft_split_count(line, ' ');
		split_a = ft_split(line, ' ');
		if (split_c < 2 || split_a == NULL || !fdf_map_fill(map, line_i, split_a, split_c))
			break ;
		ft_memfree((void **)&line);
		ft_arrayfree((void ***)&split_a, split_c);
		line_i++;
	}
	if (line != NULL)
		ft_memfree((void **)&line);
	if (split_a != NULL)
		ft_arrayfree((void ***)&split_a, split_c);
	if (line_i != map->size_y)
	{
		ft_arrayfree((void ***)&(map->xyz), line_i);
		ft_memfree((void **)&map);
		ft_puterror(6);
	}
	return (split_c);
}
