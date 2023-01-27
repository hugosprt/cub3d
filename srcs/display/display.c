#include "../../includes/cub.h"

static int	img_put_pixel(int x, int y, t_game *g, unsigned int color)
{
	char	*adrtmp;
	int		lsz;
	int		bitsz;

	adrtmp = g->adr;
	lsz = g->lsz;
	bitsz = g->bitsz;
	if (x > 0 && y > 0 && x < g->wwidth && y < g->wheight)
	{
		adrtmp += (y * lsz + (x * ((bitsz) / 8)));
		*(unsigned int *)adrtmp = color;
	}
	return (0);
}

void	rectangle_tilesize(t_game *g, unsigned int color)
{
	int	x;
	int	y;
	int	x_finish;
	int	y_finish;

	x_finish = (g->x * g->ts) + g->ts;
	y_finish = (g->y * g->ts) + g->ts;
	x = g->x * g->ts;
	while (x <= x_finish)
	{
		y = g->y * g->ts;
		while (y < y_finish)
		{
			img_put_pixel(x, y, g, color);
			y++;
		}
		x++;
	}
}

void	ft_init_bsh(t_game *g, int fx, int fy)
{
	g->dx = abs(fx - (int)g->p->x);
	if (g->p->x < fx)
		g->sx = 1;
	else
		g->sx = -1;
	g->dy = abs(fy - (int)g->p->y);
	if (g->p->y < fy)
		g->sy = 1;
	else
		g->sy = -1;
	if (g->dx > g->dy)
		g->er = g->dx / 2;
	else
		g->er = -g->dy / 2;
}

int	is_new_pos_lavab(t_game *g, float x, float y)
{
	int	tab_x;
	int	tab_y;

	if (x < 0 || x >= g->x_mmax || y < 0 || y >= g->y_mmax)
		return (1);
	tab_x = floor(x / g->ts);
	tab_y = floor(y / g->ts);
	if (tab_x < 0 || tab_y < 0 || tab_x > g->x_max || tab_y > g->y_max)
		return (1);
	if (g->tab3[tab_y][tab_x] != '1')
		return (0);
	return (1);
}

int	is_new_pos_lava(t_game *g, int x, int y)
{
	int	tab_x;
	int	tab_y;

	tab_x = (int)floor(x / g->ts);
	tab_y = (int)floor(y / g->ts);
	if (tab_x < 0 || tab_y < 0 || tab_x > g->x_max || tab_y > g->y_max)
		return (1);
	if (g->tab3[tab_y][tab_x] != '1')
		return (0);
	return (1);
}

void	ft_bsh_print(t_game *g, int fx, int fy)
{
	int	x;
	int	y;

	ft_init_bsh(g, fx, fy);
	x = g->p->x;
	y = g->p->y;
	while (1)
	{
		img_put_pixel(x, y, g, 0x00FF0000);
		if ((x == fx && y == fy))
			break ;
		g->e2 = g->er;
		if (g->e2 > -g->dx)
		{
			g->er -= g->dy;
			x += g->sx;
		}
		if (g->e2 < g->dy)
		{
			g->er += g->dx;
			y += g->sy;
		}
	}
}

void	old_pos(t_game *g,int x, int y)
{
	g->old_x = floor(x / g->ts);
	g->old_y = floor(y / g->ts);
}

void	hit_pos(t_game *g, int x, int y)
{
	g->x_intercept = x;
	g->y_intercept = y;
	g->x_wall_pos = floor(x / g->ts);
	g->y_wall_pos = floor(y / g->ts);
	g->distance = sqrt(((x - g->p->x) * (x - g->p->x))
			+ ((y - g->p->y) * (y - g->p->y)));
}

void	ft_bsh_distance(t_game *g, int fx, int fy)
{
	int	x;
	int	y;

	ft_init_bsh(g, fx, fy);
	x = g->p->x;
	y = g->p->y;
	old_pos(g, x, y);
	while (1)
	{
		if ((x == fx && y == fy) || is_new_pos_lavab(g, x, y))
			return (hit_pos(g, x, y));
		old_pos(g, x, y);
		g->e2 = g->er;
		if (g->e2 > -g->dx)
		{
			g->er -= g->dy;
			x += g->sx;
		}
		if (g->e2 < g->dy)
		{
			g->er += g->dx;
			y += g->sy;
		}
	}
}

void	player_render(t_game *g, unsigned int color)
{
	int	x;
	int	y;
	int	x_finish;
	int	y_finish;

	x_finish = g->p->x + 3;
	y_finish = g->p->y + 3;
	x = g->p->x - 2;
	while (x <= x_finish)
	{
		y = g->p->y - 3;
		while (y < y_finish)
		{
			img_put_pixel(x, y, g, color);
			y++;
		}
		x++;
	}
	x = g->p->x - (cos(g->rad) * 7);
	y = g->p->y - (sin(g->rad) * 7);
	ft_bsh_print(g, x, y);
}

void	print_map(t_game *g, char **tab)
{
	g->p->i = 1;
	g->y = -1;
	while (tab[++g->y])
	{
		g->x = -1;
		while (tab[g->y][++g->x])
		{
			if (tab[g->y][g->x] == '1')
				rectangle_tilesize(g, 0x0000FF00);
			if (tab[g->y][g->x] == '0')
				rectangle_tilesize(g, 0x000000FF);
		}
	}
	player_render(g, 0x00FF0000);
}

void calculate_offset(t_game *g, int y, int wallheight)
{
	int	distance;

	if (g->texture == 'n' || g->texture == 's')
		g->off_x = (g->x_intercept % g->ts);
	else if (g->texture == 'e' || g->texture == 'w')
		g->off_x = (g->y_intercept % g->ts);
	distance = y + (wallheight / 2) - (g->wheight / 2);
	g->off_y = distance * ((float)g->ts / wallheight);
}

void	color_the_sky_and_the_ground(t_game *g, int i, int y_s, int y_g)
{
	int	y;

	y = 0;
	while (y < g->wheight)
	{
		if (y < y_s)
			img_put_pixel(i, y, g, g->sky_color);
		if (y > y_g)
			img_put_pixel(i, y, g, g->ground_color);
		y++;
	}
}

void	info_texture(t_game *g, int texture)
{
	if (texture == 'n')
		g->adr_txt = mlx_get_data_addr(g->t_n, &g->txt_bit,
				&g->txt_lsz, &g->txt_endi);
	else if (texture == 's')
		g->adr_txt = mlx_get_data_addr(g->t_s, &g->txt_bit,
				&g->txt_lsz, &g->txt_endi);
	else if (texture == 'e')
		g->adr_txt = mlx_get_data_addr(g->t_e, &g->txt_bit,
				&g->txt_lsz, &g->txt_endi);
	else
		g->adr_txt = mlx_get_data_addr(g->t_w, &g->txt_bit,
				&g->txt_lsz, &g->txt_endi);
}

void txt_to_img_pixel_put(t_game *g, int i, int y_start)
{
	if (g->off_x >= 0 && g->off_y >= 0 && g->off_x < 65 && g->off_y < 65)
	{
		g->adr[y_start * g->lsz + i * (g->bitsz / 8)]
			= g->adr_txt[g->off_y * g->txt_lsz + g->off_x * (g->txt_bit / 8)];
		g->adr[y_start * g->lsz + i * (g->bitsz / 8) + 1]
			= g->adr_txt[g->off_y * g->txt_lsz
			+ g->off_x * (g->txt_bit / 8) + 1];
		g->adr[y_start * g->lsz + i * (g->bitsz / 8) + 2]
			= g->adr_txt[g->off_y * g->txt_lsz
			+ g->off_x * (g->txt_bit / 8) + 2];
	}
}

void	draw_ray(t_game *g, int i)
{
	int		y_start;
	int		y_finish;
	float	wall_height;
	float	projection_plane;

	g->distance = cos(g->radr - g->rad) * g->distance;
	projection_plane = ((g->wwidth / 2) / tan((g->fov / 2)));
	wall_height = (g->ts / g->distance) * projection_plane;
	y_start = (g->wheight / 2) - (wall_height / 2);
	y_finish = (g->wheight / 2) + (wall_height / 2);
	color_the_sky_and_the_ground(g, i, y_start, y_finish);
	info_texture(g, g->texture);
	while (y_start <= y_finish)
	{
		if ((y_start > 0 && y_start < g->wheight
				&& i > 0 && i < g->wwidth))
		{
			calculate_offset(g, y_start, wall_height);
			txt_to_img_pixel_put(g, i, y_start);
		}
		y_start++;
	}
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

float distance(int x1, int y1, int x2, int y2)
{
	float	distance;

	distance = sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));

	return (distance);
}

void	rectangle_window_size(t_game *g, unsigned int color)
{
	int	x;
	int	y;
	int	x_finish;
	int	y_finish;

	x_finish = g->wwidth;
	y_finish = g->wheight;
	x = 0;
	while (x <= x_finish)
	{
		y = 0;
		while (y < y_finish)
		{
			img_put_pixel(x, y, g, color);
			y++;
		}
		x++;
	}
}

void	calculate_texture(t_game *g)
{
	if ((g->old_x == g->x_wall_pos) && (g->old_y < g->y_wall_pos))
		g->texture = 'n';
	if ((g->old_x == g->x_wall_pos) && (g->old_y > g->y_wall_pos))
		g->texture = 's';
	if ((g->old_x < g->x_wall_pos) && (g->old_y == g->y_wall_pos))
		g->texture = 'e';
	if ((g->old_x > g->x_wall_pos) && (g->old_y == g->y_wall_pos))
		g->texture = 'w';
}

void	ft_find_distance(t_game *g, float rad)
{
	int	x;
	int	y;

	g->radr = rad;
	x = g->p->x - (cos(rad) * 10000);
	y = g->p->y - (sin(rad) * 10000);
	ft_bsh_distance(g, x, y);
	calculate_texture(g);
}

void ray_cast(t_game *g)
{
	int		id;
	float	firstrad;
	float	step;

	g->p->i = 1;
	if (is_new_pos_lava(g, g->p->x, g->p->y))
		return (rectangle_window_size(g, 255255255));
	step = (60 * (PI / 180)) / g->wwidth;
	firstrad = g->rad - (step * (g->wwidth / 2));
	id = 0;
	while (id < 1200)
	{
		ft_find_distance(g, firstrad);
		draw_ray(g, id);
		firstrad += step;
		id++;
	}
}

int	render(t_game *g)
{
	if (g->step == 0 && g->side == 0 && g->turn == 0 && g->p->i > 0)
		return (0);
	else if (g->p->i > 0)
		update_player(g);
	g->img = mlx_new_image(g->mlx, g->wwidth, g->wheight);
	if (!g->img)
		return (ft_putstr_fd("Error new image\n", 2), 1);
	g->adr = mlx_get_data_addr(g->img, &g->bitsz, &g->lsz, &g->endi);
	if (is_new_pos_lava(g, g->p->x, g->p->y))
		print_map(g, g->tab3);
	else
		ray_cast(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	mlx_destroy_image(g->mlx, g->img);
	return (0);
}
