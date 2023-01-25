#ifndef STRUCT_H
# define STRUCT_H

# define TRUE 1
# define FALSE 0
# define PI 3.141592653589793



typedef struct s_player{
	float	x;
	float	y;
	int		a;
	int		i;
}	t_player;

typedef struct s_ray{
	int				id;
	float			radr;
	float			distance;
	int				texture;
	int				x_intercept;
	int				y_intercept;
	int				x_wall_pos;
	int				y_wall_pos;
	int				old_x;
	int				old_y;
	struct s_ray	*next;
}	t_ray;

typedef struct s_game {
	int x;
    int y;
    int     is_valid;
    char    is_player;
    int     fd;
    char    **tab;
    char    **tab2;
    char    **tab3;
	int		x_max;
	int		y_max;
	int		x_mmax;
	int		y_mmax;
    char    *NO_texture;
    char    *SO_texture;
    char    *WE_texture;
    char    *EA_texture;
    char     texture;
    char    *floor_rgb;
    char    *ceiling_rgb;
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
	t_ray		*ray;
	int			dy;
	int			dx;
	int			sx;
	int			sy;
	int			er;
	int			e2;
	int			step;
	int			side;
	int			turn;
	float		radr;
	int		x_intercept;
	int		y_intercept;
	int		x_wall_pos;
	int		y_wall_pos;
	int 	old_x;
	int		old_y;
	t_ray	*c_ray;
	char		**map;
}	t_game;

#endif