#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_player{
	N = 'N',
	S = 'S',
	E = 'E',
	W = 'W',

}	t_player;

typedef struct s_game{

    void    *mlx;
    void    *win;

    int x;
    int y;
    int     ground_color;
    int     sky_color;
    int     is_valid;
    char    is_player;
    int     fd;
    char    **tab;
    char    **tab2;
    t_player        player;

}   t_game;

#endif