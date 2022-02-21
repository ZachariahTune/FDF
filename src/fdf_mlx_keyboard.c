#include "fdf.h"

static void	fdf_mlx_hook_keydown_help_1(int key, t_map *map)
{
	if (key == 12 && map->zscale < 2)					//Key "Q" (ZScale+)
		map->zscale = map->zscale + 0.1;
	if (key == 0 && map->zscale > 0.01)					//Key "A" (ZScale-)
		map->zscale = map->zscale - 0.1;
	if (key == 13)										//Key "W" (OXY+)
		map->oxy = map->oxy + (FDF_PI / 180 * 5);
	if (key == 1)										//Key "S" (OXY-)
		map->oxy = map->oxy - (FDF_PI / 180 * 5);
	if (key == 14)										//Key "E" (OXZ+)
		map->oxz = map->oxz + (FDF_PI / 180 * 5);
	if (key == 2)										//Key "D" (OXZ-)
		map->oxz = map->oxz - (FDF_PI / 180 * 5);
	if (key == 15)										//Key "R" (OYZ+)
		map->oyz = map->oyz + (FDF_PI / 180 * 5);
	if (key == 3)										//Key "F" (OYZ-)
		map->oyz = map->oyz - (FDF_PI / 180 * 5);
	if (key == 16 && map->pers < 0.00099)				//Key "T" (Pers+)
		map->pers = map->pers + 0.0001;
	if (key == 4 && map->pers > 0.00001)				//Key "G" (Pers-)
		map->pers = map->pers - 0.0001;
}

static void	fdf_mlx_hook_keydown_help_2(int key, t_map *map)
{
	if (key == 29)										//Key "0"
	{
		map->zscale = 1.0;
		map->zoom = map->zoom_orig;
		map->oxy = FDF_PI / 180 * 35;
		map->oxz = 0;
		map->oyz = FDF_PI / 180 * 50;
		map->pers = 0.0;
		map->mlx->img->shift_x = MLX_IMG_W / 2;
		map->mlx->img->shift_y = MLX_WIN_H / 2;
	}
	if (key == 24 && map->zoom < (map->zoom_orig * 3))	//Key "+"
		map->zoom = map->zoom + (map->zoom_orig / 10);
	if (key == 27 && map->zoom > (map->zoom_orig / 2))	//Key "-"
		map->zoom = map->zoom - (map->zoom_orig / 10);
	if (key == 123)										//Key "Left"
		map->mlx->img->shift_x = map->mlx->img->shift_x - 10;
	if (key == 124)										//Key "Right"
		map->mlx->img->shift_x = map->mlx->img->shift_x + 10;
	if (key == 125)										//Key "Down"
		map->mlx->img->shift_y = map->mlx->img->shift_y + 10;
	if (key == 126)										//Key "Up"
		map->mlx->img->shift_y = map->mlx->img->shift_y - 10;
}

int		fdf_mlx_hook_keydown(int key, t_map *map)
{
	if (key == 53)										//Key "Esc"
	{
		fdf_mlx_destroy(map->mlx);
		ft_arrayfree((void ***)&(map->xyz), map->size_y);
		ft_memfree((void **)&map);
		ft_puterror(98);
	}
	if ((key >= 0 && key <= 4) || (key >= 12 && key <= 16) || key == 24 || key == 27 || key == 29 || (key >= 123 && key <= 126))
	{
		map->color = 0;
		fdf_mlx_map_print(map->mlx->img, map);
		if ((key >= 0 && key <= 4) || (key >= 12 && key <= 16))
			fdf_mlx_hook_keydown_help_1(key, map);
		else
			fdf_mlx_hook_keydown_help_2(key, map);
		map->color = 1;
		fdf_mlx_map_print(map->mlx->img, map);
		mlx_put_image_to_window(map->mlx, map->mlx->win, map->mlx->img->img, MLX_MENU_W, 0);
	}
	return (0);
}
