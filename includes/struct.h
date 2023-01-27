#ifndef STRUCT_H
# define STRUCT_H

# define TRUE 1
# define FALSE 0
# define PI 3.141592653589793



typedef struct s_player{
	float	x;
	float	y;
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

typedef struct s_texture{
	int			lsz;
	int			bitsz;
	int			endi;
	void		*mlx_xmp;
	void		*data;
	char		*adr;
}	t_texture;

typedef struct s_game {
	int			x;
	int			y;
	int			is_valid;
	char		is_player;
	int			fd;
	char		**tab;
	char		**tab2;
	char		**tab3;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	char		*floor_rgb;
	char		*ceiling_rgb;
	int			truc_parse;
	t_texture	*t_n;
	t_texture	*t_s;
	t_texture	*t_e;
	t_texture	*t_w;
	void		*mlx;
	void		*win;
	int			ts;
	int			wheight;
	int			wwidth;
	void		*img;
	int			lsz;
	int			bitsz;
	int			endi;
	char		*adr;
	int			ground_color;
	int			sky_color;
	t_player	*p;
	float		fov;
	int			step_speed;
	int			side_speed;
	float		rotation_speed;
	int			step;
	int			side;
	int			turn;
	float		rad;
	int			dy;
	int			dx;
	int			sx;
	int			sy;
	int			er;
	int			e2;
	t_ray		*ray;
	float		radr;
	float		distance;
	int			x_intercept;
	int			y_intercept;
	int			x_wall_pos;
	int			y_wall_pos;
	int			old_x;
	int			old_y;
	int			texture;
	t_ray		*c_ray;
	char		**map;
	int			x_max;
	int			y_max;
	int			x_mmax;
	int			y_mmax;
	int			off_x;
	int			off_y;
	char		*adr_txt;
	int			txt_lsz;
	int			txt_bit;
	int			txt_endi;
}	t_game;

#endif