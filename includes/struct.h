#ifndef STRUCT_H
# define STRUCT_H

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
    char    *NO_texture;
    char    *SO_texture;
    char    *WE_texture;
    char    *EA_texture;
    int     texture;
    char    *floor_rgb;
    char     *ceiling_rgb;
    int     truc_parse;


}   t_game;

#endif