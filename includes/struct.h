#ifndef STRUCT_H
# define STRUCT_H

# define PI 3.141592653589793

typedef struct s_player{
	float	x;
	float	y;
	int		a;
	int		i;
}	t_player;

typedef struct s_game{
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
	int			x;
	int			y;
	int			dy;
	int			dx;
	int			sx;
	int			sy;
	int			er;
	int			e2;
	int			step;
	int			side;
	int			turn;
	char		**tab;
}	t_game;

#endif