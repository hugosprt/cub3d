#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_game{

    void    *mlx;
    void    *win;

    int     ground_color;
    int     sky_color;
}   t_game;

#endif