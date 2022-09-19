/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hspriet <hspriet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:41:50 by hspriet           #+#    #+#             */
/*   Updated: 2022/04/26 17:23:07 by hspriet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

# define BUFFER_SIZE 1

typedef struct s_img {
	void	*img;
	char	*addr;
	int		img_width;
	int		img_height;
}				t_img;

enum {
	PLAYER,
	COLLEC,
	EXIT,
	GRASS,
	WALL,
	WALL2,
	WALL3,
	WALL4
};

typedef struct s_root {
	void	*mlx;
	void	*win;
	int		is_player;
	int		is_collect;
	int		is_exit;
	int		is_wall;
	int		is_valid;
	t_img	txtr[9];
	int		size;
	int		x;
	int		xx;
	int		y;
	int		yy;
	int		fd;
	int		step;
	char	**tab;
}				t_root;

int		is_finish(t_root *root);
void	check_img(t_root *root);
void	crash(t_root *root, char **tab);
void	finish(t_root *root, char **tab);
void	throw_error(t_root *root, char *tab);
void	struct_init(t_root *root, char *file);
void	mid(t_root *root, char *av);
char	*parse(t_root *root);
void	firstlast(t_root *root, char *av);
void	print_tiles(t_root *root, char **tab);
char	*get_next_line(int fd);
void	init_img(t_root *root, char **tab);
void	move_right(t_root *root, char **tab);
void	move_left(t_root *root, char **tab);
void	move_down(t_root *root, char **tab);
void	move_up(t_root *root, char **tab);
void	print_txtr(t_root *root, int x, int y, int type);
#endif
