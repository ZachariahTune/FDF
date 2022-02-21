#include "fdf.h"

static void	fdf_mlx_hook_mouse_scroll(int button, int x, int y, t_map *map)
{
	double	shift_x_rel;
	double	shift_y_rel;

	shift_x_rel = ((double)x - MLX_MENU_W - map->mlx->img->shift_x) / MLX_IMG_W;
	shift_y_rel = ((double)y - map->mlx->img->shift_y) / MLX_WIN_H;
	map->color = 0;
	fdf_mlx_map_print(map->mlx->img, map);
	if (button == 4 && map->zoom < (map->zoom_orig * 3))
	{
		map->zoom += map->zoom_orig / 10;
		map->mlx->img->shift_x -= MLX_IMG_W / 20 * shift_x_rel;
		map->mlx->img->shift_y -= MLX_WIN_H / 20 * shift_y_rel;

	}
	if (button == 5 && map->zoom > (map->zoom_orig / 2))
	{
		map->zoom -= map->zoom_orig / 10;
		map->mlx->img->shift_x += MLX_IMG_W / 20 * shift_x_rel;
		map->mlx->img->shift_y += MLX_WIN_H / 20 * shift_y_rel;
	}
	map->color = 1;
	fdf_mlx_map_print(map->mlx->img, map);
	mlx_put_image_to_window(map->mlx, map->mlx->win, map->mlx->img->img, MLX_MENU_W, 0);
}

int		fdf_mlx_hook_mouse_down(int button, int x, int y, t_map *map)
{
	if (x > MLX_MENU_W && y > 0)
	{
		if (button == 4 || button == 5)
			fdf_mlx_hook_mouse_scroll(button, x, y, map);
		if (button == 1)
			map->mouse_press = 1;
	}
	return (0);
}

int		fdf_mlx_hook_mouse_up(int button, int x, int y, t_map *map)
{
	(void)x;
	(void)y;
	if (button == 1)
		map->mouse_press = 0;
	return (0);
}

int		fdf_mlx_hook_mouse_move(int x, int y, t_map *map)
{
	static int	x_temp;
	static int	y_temp;

	if (map->mouse_press == 0)
	{
		x_temp = 0;
		y_temp = 0;
	}
	if (map->mouse_press == 1)
	{
		map->color = 0;
		fdf_mlx_map_print(map->mlx->img, map);
		if (x_temp != 0 && y_temp != 0)
		{
			map->oxz += (x - x_temp) * 0.002;
			map->oyz -= (y - y_temp) * 0.002;
		}
		x_temp = x;
		y_temp = y;
		map->color = 1;
		fdf_mlx_map_print(map->mlx->img, map);
		mlx_put_image_to_window(map->mlx, map->mlx->win, map->mlx->img->img, MLX_MENU_W, 0);
	}
	return (0);
}
