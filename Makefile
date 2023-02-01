NAME        = cub3D 
CC            = cc
CFLAGS        = -Wall -Werror -Wextra -g
# CFLAGS        += -fsanitize=address -g3
SRCS         = srcs/main.c \
				srcs/gnl/get_next_line.c\
				srcs/gnl/get_next_line_utils.c\
				srcs/errors/error.c \
				srcs/parse/parse.c \
				srcs/parse/parse2.c \
				srcs/parse/parse3.c \
				srcs/parse/check_map.c \
				srcs/parse/check_map2.c \
				srcs/parse/check_map3.c \
				srcs/parse/error.c \
				srcs/parse/free_func.c \
				srcs/parse/utils.c \
				srcs/parse/rgb.c \
				srcs/display/display.c \
				srcs/display/player_init.c \
				srcs/display/textures.c \
				srcs/display/mini_map.c \
				srcs/display/pixel_puts.c \
				srcs/display/ray_casting.c \
				srcs/display/i_like_to_move_it.c \

OBJS        = $(SRCS:.c=.o)
LIBFT        = libft/libft.a
MLX            = -L ./minilibx/ -lmlx -lXext -lX11 -lm -O3
#MLX             = -Lmlx -lmlx -framework OpenGL -framework AppKit
INCLUDE        = -I/usr/include -Imlx_linux
#INCLUDE        = -I

all : $(NAME)

%.o: %.c
	$(CC) ${CFLAGS} ${INCLUDE} -c $< -o $@

$(NAME): $(OBJS)
	@make -C libft/
	@echo " Compiling Libft..."
	$(CC) $(OBJS) -I . -o $(NAME) ${LIBFT} ${MLX}

clean : 
	rm -f $(OBJS)
	make clean -C libft/

fclean : clean
	rm -f $(NAME)

re : fclean all
