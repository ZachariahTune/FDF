#include "fdf.h"

//Поиск максимального Z
static int	fdf_max_z(t_map *map)
{
	int	z_max;
	int	y;
	int x;

	z_max = 0;
	y = 0;
	while (y < map->size_y)
	{
		x = 0;
		while (x < map->size_x)
		{
			if (map->xyz[y][x] > z_max)
				z_max = map->xyz[y][x];
			x++;
		}
		y++;
	}
	return (z_max);
}

//Заливка подложки меню фоном
static void	fdf_mlx_menu_background(t_map *map, int x, int y)
{
	while (x < MLX_MENU_W)
	{
		y = 0;
		while (y < MLX_WIN_H)
		{
			fdf_mlx_pixel_put(map->mlx->img, x, y, MLX_COLOR_G);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(map->mlx, map->mlx->win, map->mlx->img->img, 0, 0);
	x = 0;
	while (x < MLX_MENU_W)
	{
		y = 0;
		while (y < MLX_WIN_H)
		{
			fdf_mlx_pixel_put(map->mlx->img, x, y, MLX_COLOR_B);
			y++;
		}
		x++;
	}
}

//Распечатка меню
static void	fdf_mlx_menu_print(t_map *map)
{
	int		y;
	void	*mlx;
	void	*win;
	
	y = 0;
	mlx = map->mlx->mlx;
	win = map->mlx->win;
	mlx_string_put(mlx, win, 16, y += 30, 0xFFFFFF, "Control buttons");
	mlx_string_put(mlx, win, 16, y += 15, 0xFFFFFF, "---------------");
	mlx_string_put(mlx, win, 16, y += 35, 0xFFFFFF, "Zoom buttons: +/-");
	mlx_string_put(mlx, win, 16, y += 30, 0xFFFFFF, "Mouse zoom: scroll");
	mlx_string_put(mlx, win, 16, y += 30, 0xFFFFFF, "Z-Scale: Q/A");
	mlx_string_put(mlx, win, 16, y += 30, 0xFFFFFF, "Perspective: Y/H");
	mlx_string_put(mlx, win, 16, y += 30, 0xFFFFFF, "Rotation buttons:");
	mlx_string_put(mlx, win, 36, y += 30, 0xFFFFFF, "Z-Axis: W/S");
	mlx_string_put(mlx, win, 36, y += 30, 0xFFFFFF, "Y-Axis: E/D");
	mlx_string_put(mlx, win, 36, y += 30, 0xFFFFFF, "X-Axis: R/F");
	mlx_string_put(mlx, win, 16, y += 30, 0xFFFFFF, "Mouse rotation: D&D");
	mlx_string_put(mlx, win, 16, y += 30, 0xFFFFFF, "Move: 4 arrows");
	mlx_string_put(mlx, win, 16, y += 30, 0xFFFFFF, "---------------");
	mlx_string_put(mlx, win, 16, y += 30, 0xFFFFFF, "Default position: 0");
}

//Закрытие окна крестиком
static int	fdf_close_window(t_map *map)
{
	fdf_mlx_destroy(map->mlx); // <- ???
	ft_arrayfree((void ***)&(map->xyz), map->size_y); // <- ???
	ft_memfree((void **)&map); // <- ???
	ft_puterror(99);
	return (0);
}

//Основная функция
int		main(int argc, char **argv)
{
	int		fd[2];
	t_map	*map;

	fdf_open_mapfile(argc, argv[1], &fd[0], &fd[1]);
	map = fdf_map_init();
	map->size_y = fdf_preread_map(fd[0], map);
	map->size_x = fdf_read_map(fd[1], map, 0, 0);
	map->size_z = fdf_max_z(map);
	map->mlx = fdf_mlx_init(map);
	fdf_mlx_menu_background(map, 0, 0);
	fdf_mlx_map_print(map->mlx->img, map);
	mlx_hook(map->mlx->win, 2, 0, fdf_mlx_hook_keydown, map);
	mlx_hook(map->mlx->win, 17, 0, fdf_close_window, map);
	mlx_hook(map->mlx->win, 4, 0, fdf_mlx_hook_mouse_down, map);
	mlx_hook(map->mlx->win, 6, 0, fdf_mlx_hook_mouse_move, map);
	mlx_hook(map->mlx->win, 5, 0, fdf_mlx_hook_mouse_up, map);
	mlx_put_image_to_window(map->mlx, map->mlx->win, map->mlx->img->img, MLX_MENU_W, 0);
	fdf_mlx_menu_print(map);
	mlx_loop(map->mlx->mlx);
	return (0);
}
