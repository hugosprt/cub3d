#ifndef STRUCT_H
# define STRUCT_H

# define PI 3.141592653589793

typedef struct s_player{
	float	x;
	float	y;
	int		a;
	int		i;
}	t_player;

typedef struct s_game {
	 int x;
    int y;

    int     is_valid;
    char    is_player;
    int     fd;
    char    **tab;
	char    **tab4;
    char    **tab2;
    char    **tab3;
    char    *NO_texture;
    char    *SO_texture;
    char    *WE_texture;
    char    *EA_texture;
    int     texture;
    char    *floor_rgb;
    char     *ceiling_rgb;
    int     truc_parse;
    int     NO;
    int     SO;
    int     EA;
    int     WE;
	void		*mlx;
	void		*win;
	void		*img;
	int			lsz;
	int			bitsz;
	int			endi;
	char		*adr;
	int			ground_color;
	int			sky_color;
	t_player	*p;
	int			ts;
	int			wheight;
	int			wwidth;
	float		step_speed;
	int			rotation_speed;
	float		rad;
	float		fov;
	float		distance;
	int			dy;
	int			dx;
	int			sx;
	int			sy;
	int			er;
	int			e2;
	int			step;
	int			side;
	int			turn;
}	t_game;

#endif