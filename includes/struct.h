#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_img {
	void	*img;
	char	*addr;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct s_player{

    int     x;
    int     y;
    int     A;
}   t_player;

typedef struct s_game{

    void        *mlx;
    void        *win;
    int         ground_color;
    int         sky_color;
    t_player    *p;
    t_img	txtr[9];
	int		size;
	int		x;
	int		xx;
	int		y;
	int		yy;
	int		fd;
	int		step;
	char	**tab;
}   t_game;


#endif