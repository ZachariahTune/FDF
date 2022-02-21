#include "fdf.h"

//ДЕинициализация изображения
t_img	*fdf_image_destroy(t_mlx *mlx, t_img *img)
{
	if (img->img != NULL)
		mlx_destroy_image(mlx->mlx, img->img);
	ft_memfree((void **)&img);
	return (NULL);
}

//Инициализация изображения
t_img	*fdf_image_new(t_mlx *mlx)
{
	t_img		*img;

	img = (t_img *)malloc(sizeof(t_img));
	if (img == NULL)
		return (NULL);
	img->img = mlx_new_image(mlx->mlx, MLX_IMG_W, MLX_WIN_H);
	if (img->img == NULL)
		return (fdf_image_destroy(mlx, img));
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->step, &img->end);
	img->x1 = 0;
	img->x2 = 0;
	img->y1 = 0;
	img->y2 = 0;
	img->shift_x = MLX_IMG_W / 2;
	img->shift_y = MLX_WIN_H / 2;
	return (img);
}

//ДЕинициализация библеотеки MLX
t_mlx	*fdf_mlx_destroy(t_mlx *mlx)
{
	if (mlx->win != NULL)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->img != NULL)
		fdf_image_destroy(mlx, mlx->img);
	ft_memfree((void **)&mlx);
	return (NULL);
}

//Инициализация библеотеки MLX
static t_mlx	*fdf_mlx_init_return(void)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (mlx == NULL)
		return (NULL);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, MLX_WIN_W, MLX_WIN_H, "FDF");
	mlx->img = fdf_image_new(mlx);
	if (mlx->mlx == NULL || mlx->win == NULL || mlx->img == NULL)
		return (fdf_mlx_destroy(mlx));
	return (mlx);
}

t_mlx	*fdf_mlx_init(t_map *map)
{
	t_mlx	*mlx;

	mlx = fdf_mlx_init_return();
	if (mlx == NULL)
	{
		ft_arrayfree((void ***)&(map->xyz), map->size_y);
		ft_memfree((void **)&map);
		ft_puterror(7);
	}
	//Подбор оптимального масштаба
	map->zoom = ft_min((MLX_IMG_W / 5 * 3 / (map->size_x - 1)), (MLX_WIN_H / 8 * 7 / (map->size_y - 1)));
	map->zoom_orig = map->zoom;
	return (mlx);
}
