#include "fdf.h"

//Рисование одной точки
void	fdf_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	if (x < 0 || x >= MLX_IMG_W || y < 0 || y >= MLX_WIN_H)
		return ;
	*(unsigned int *)(img->addr + (y * img->step + x * (img->bpp / 8))) = color;
}

//Рисование линии по двум точкам
static void	fdf_mlx_line_put(t_img *img, t_map *map)
{
	double	dif_x;
	double	dif_y;
	double	dif_m;
	int		dif_i;
	int		print_x;
	int		print_y;

	dif_x = img->x2 - img->x1;
	dif_y = img->y2 - img->y1;
	dif_m = ft_max(ft_abs(dif_x), ft_abs(dif_y));
	dif_i = 0;
	while (dif_i < dif_m)
	{
		print_x = img->x1 + (dif_x / dif_m * dif_i);
		print_y = img->y1 + (dif_y / dif_m * dif_i);
		if (map->color == 1)
			fdf_mlx_pixel_put(img, print_x, print_y, MLX_COLOR_W);
		if (map->color == 0)
			fdf_mlx_pixel_put(img, print_x, print_y, MLX_COLOR_B);
		dif_i++;
	}
	if (map->color == 1)
		fdf_mlx_pixel_put(img, img->x2, img->y2, MLX_COLOR_W);
	if (map->color == 0)
		fdf_mlx_pixel_put(img, img->x2, img->y2, MLX_COLOR_B);
}

//Вычисление координат первой точки перед рисованием линии
static void	fdf_mlx_x1y1_calculate(t_img *img, t_map *map, int x, int y)
{
	double	x_old;
	double	y_old;
	double	z_old;
	double	x_new;
	double	y_new;
	double	z_new;

	x_old = x - (map->size_x - 1) / 2;
	y_old = y - (map->size_y - 1) / 2;
	z_old = map->xyz[y][x] * map->zscale - (map->size_z * map->zscale - 1) / 2;
	x_new = x_old * cos(map->oxy) - y_old * sin(map->oxy);
	y_new = x_old * sin(map->oxy) + y_old * cos(map->oxy);
	x_old = x_new;
	y_old = y_new;
	x_new = x_old * cos(map->oxz) + z_old * sin(map->oxz);
	z_new = z_old * cos(map->oxz) - x_old * sin(map->oxz);
	x_old = x_new;
	z_old = z_new;
	y_new = y_old * cos(map->oyz) - z_old * sin(map->oyz);
	z_new = y_old * sin(map->oyz) + z_old * cos(map->oyz);
	x_new = x_old / (1 - map->pers * map->zoom_orig * z_new);
	y_new = y_new / (1 - map->pers * map->zoom_orig * z_new);
	img->x1 = x_new * map->zoom + map->mlx->img->shift_x;
	img->y1 = y_new * map->zoom + map->mlx->img->shift_y;
}

//Вычисление координат второй точки для рисования линии
static void	fdf_mlx_x2y2_calculate(t_img *img, t_map *map, int x, int y)
{
	double	x_old;
	double	y_old;
	double	z_old;
	double	x_new;
	double	y_new;
	double	z_new;

	x_old = x - (map->size_x - 1) / 2;
	y_old = y - (map->size_y - 1) / 2;
	z_old = map->xyz[y][x] * map->zscale - (map->size_z * map->zscale - 1) / 2;
	x_new = x_old * cos(map->oxy) - y_old * sin(map->oxy);
	y_new = x_old * sin(map->oxy) + y_old * cos(map->oxy);
	x_old = x_new;
	y_old = y_new;
	x_new = x_old * cos(map->oxz) + z_old * sin(map->oxz);
	z_new = z_old * cos(map->oxz) - x_old * sin(map->oxz);
	x_old = x_new;
	z_old = z_new;
	y_new = y_old * cos(map->oyz) - z_old * sin(map->oyz);
	z_new = y_old * sin(map->oyz) + z_old * cos(map->oyz);
	x_new = x_old / (1 - map->pers * map->zoom_orig * z_new);
	y_new = y_new / (1 - map->pers * map->zoom_orig * z_new);
	img->x2 = x_new * map->zoom + map->mlx->img->shift_x;
	img->y2 = y_new * map->zoom + map->mlx->img->shift_y;
	fdf_mlx_line_put(img, map);
}

//Перебор точек для вывода карты в виде изображения
void	fdf_mlx_map_print(t_img *img, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->size_y)
	{
		x = 0;
		while (x < map->size_x)
		{
			fdf_mlx_x1y1_calculate(img, map, x, y);
			if (x + 1 < map->size_x)
				fdf_mlx_x2y2_calculate(img, map, (x + 1), y);
			if (y + 1 < map->size_y)
				fdf_mlx_x2y2_calculate(img, map, x, (y + 1));
			x++;
		}
		y++;
	}
}
