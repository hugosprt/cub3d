# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/03 14:17:45 by rpol              #+#    #+#              #
#    Updated: 2022/07/29 16:40:36 by rpol             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = 
MLXFLAGS = -lXext -lX11 -lm

NAME = fdf
SRCS_NAME = fdf.c ft_linkinit.c ft_parsing.c get_next_line.c \
			get_next_line_utils.c ft_draw.c
SRCS_PATH = srcs
SRCS = $(addprefix $(SRCS_PATH)/, $(SRCS_NAME))
INCS_NAME = fdf.h
INCS_PATH = includes
INCS = $(addprefix $(INCS_PATH)/, $(INCS_NAME))
LIBS = libft/libft.a \
		minilibx/libmlx_Linux.a
RM = rm -rf
OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o : %.c
			${CC} ${CFLAGS} -g -I ${INCS_PATH} -I libft -I minilibx -c $< -o $@

${LIBS}:
			make -C libft; make -C minilibx

${NAME}:	${OBJS} ${INCS} ${LIBS}
			${CC} -g -o ${NAME} ${OBJS} ${LIBS} ${MLXFLAGS}
clean:
			${RM} ${OBJS}; make -C libft clean; make -C minilibx clean

fclean:		clean
			${RM} ${NAME}; make -C libft fclean

re:			fclean all

.PHONY : all clean fclean re