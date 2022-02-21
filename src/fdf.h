#ifndef FDF_H
# define FDF_H

# include <math.h>
# include "libft.h"
# include "mlx.h"
# define MLX_WIN_W 1248
# define MLX_WIN_H 768
# define MLX_MENU_W 224
# define MLX_IMG_W 1024
# define MLX_COLOR_W 0x00ffffff
# define MLX_COLOR_B 0x00000000
# define MLX_COLOR_G 0x00444444
# define FDF_PI 3.141592653589793

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			step;
	int			end;
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			shift_x;
	int			shift_y;
}	t_img;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_img		*img;
}	t_mlx;

typedef struct s_map
{
	int			size_x;
	int			size_y;
	int			size_z;
	int			**xyz;
	int			color;
	double		zscale;
	double		zoom;
	double		zoom_orig;
	double		oxy;
	double		oxz;
	double		oyz;
	double		pers;
	int			mouse_press;
	t_mlx		*mlx;
}	t_map;

//fdf_puts.c
void	ft_putstr(char *str);
void	ft_puterror(int code);
//fdf_reader.c
void	fdf_open_mapfile(int argc, char *filename, int *fd1, int *fd2);
t_map	*fdf_map_init(void);
int		fdf_preread_map(int fd, t_map *map);
int		fdf_read_map(int fd, t_map *map, int line_i, int split_c);
//fdf_mlx_init.c
t_img	*fdf_image_destroy(t_mlx *mlx, t_img *img);
t_img	*fdf_image_new(t_mlx *mlx);
t_mlx	*fdf_mlx_destroy(t_mlx *mlx);
t_mlx	*fdf_mlx_init(t_map *map);
//fdf_mlx_draw.c
void	fdf_mlx_pixel_put(t_img *img, int x, int y, int color);
void	fdf_mlx_map_print(t_img *img, t_map *map);
//fdf_mlx_keyboard.c
int		fdf_mlx_hook_keydown(int key, t_map *map);
//fdf_mlx_mouse.c
int		fdf_mlx_hook_mouse_down(int button, int x, int y, t_map *map);
int		fdf_mlx_hook_mouse_up(int button, int x, int y, t_map *map);
int		fdf_mlx_hook_mouse_move(int x, int y, t_map *map);

#endif
