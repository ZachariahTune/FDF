NAME	=	libft.a
SRCS	=	ft_max.c ft_min.c ft_abs.c ft_abs_double.c ft_strlen.c \
			ft_memset.c ft_memcpy.c ft_strdup.c ft_memfree.c ft_arrayfree.c \
			ft_atoi.c ft_gnl.c ft_split.c
			
OBJS	=	$(SRCS:.c=.o)

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g
RM 		= 	rm -f

all: 		$(NAME)

%.o:%.c
			$(CC) $(CFLAGS) -I . -o $@ -c $<

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)
			ranlib $(NAME)

clean:
			${RM} $(OBJS)

fclean:		clean
			${RM} ${NAME}

re:			fclean $(NAME)

.PHONY:		all clean fclean re
