# Основная директория проекта
SRC_DIR	=	./src/

# Библеотека LibFT
FT_DIR	=	./libft/
FT_LIB	=	$(FT_DIR)libft.a
FT_LNK	=	-L $(FT_DIR) -l ft

# Библеотека MLX
MLX_DIR	=	./minilibx/
MLX_LIB	=	$(MLX_DIR)libmlx.a
MLX_LNK	=	-L $(MLX_DIR) -l mlx -framework OpenGL -framework AppKit

# Параметры сборки и удаления
NAME	=	fdf
SRCS	=	main.c fdf_puts.c fdf_reader.c fdf_mlx_init.c \
			fdf_mlx_draw.c fdf_mlx_keyboard.c fdf_mlx_mouse.c
OBJS	=	$(addprefix $(SRC_DIR),$(SRCS:.c=.o))
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g
RM 		= 	rm -f

all:		$(FT_LIB) $(MLX_LIB) $(NAME)

$(SRC_DIR)%.o:$(SRC_DIR)%.c
			$(CC) $(CFLAGS) -I $(FT_DIR) -I $(MLX_DIR) -I $(SRC_DIR) -o $@ -c $< -Ofast

$(FT_LIB):
			make -C $(FT_DIR)

$(MLX_LIB):
			make -C $(MLX_DIR)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(FT_LNK) -Ofast $(MLX_LNK) -lm -o $(NAME)

clean:
			${RM} $(OBJS)
			make -C $(FT_DIR) clean
			make -C $(MLX_DIR) clean

fclean:		clean
			make -C $(FT_DIR) fclean
			${RM} $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
