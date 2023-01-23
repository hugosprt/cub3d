NAME        = cub3D 
CC            = cc
CFLAGS        = -Wall -Werror -Wextra -g
# CFLAGS        += -fsanitize=address -g3
SRCS         = srcs/main.c \
				srcs/gnl/get_next_line.c\
				srcs/gnl/get_next_line_utils.c\
				srcs/errors/error.c \
				srcs/parse/parse.c \
				srcs/display/display.c \
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
