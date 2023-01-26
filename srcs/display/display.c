#include "../../includes/cub.h"

static int	img_put_pixel(int x, int y, t_game *v, unsigned int color)
{
	char	*adrtmp;
	int		lsz;
	int		bitsz;

	adrtmp = v->adr;
	lsz = v->lsz;
	bitsz = v->bitsz;
	if (x > 0 && y > 0 && x < v->wwidth && y < v->wheight)
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

void	ft_init_bsh(t_game *v, int fx, int fy)
{
	v->dx = abs(fx - (int)v->p->x);
	if (v->p->x < fx)
		v->sx = 1;
	else
		v->sx = -1;
	v->dy = abs(fy - (int)v->p->y);
	if (v->p->y < fy)
		v->sy = 1;
	else
		v->sy = -1;
	if (v->dx > v->dy)
		v->er = v->dx / 2;
	else
		v->er = -v->dy / 2;
}

int	is_new_pos_lavab(t_game *g, float x, float y)
{
	int	tab_x;
	int	tab_y;

	if (x < 0 || x >= g->wwidth || y < 0 || y >= g->wheight)
		return (1);
	tab_x = floor(x / g->ts);
	tab_y = floor(y / g->ts);
	if (g->map[tab_y][tab_x] != '1')
		return (0);
	return (1);
}

int	is_new_pos_lava(t_game *g, int x, int y)
{
	int	tab_x;
	int	tab_y;

	tab_x = (int)floor(x / g->ts);
	tab_y = (int)floor(y / g->ts);
	if (tab_x < 0 || tab_y < 0 || tab_x > g->x_mmax || tab_y > g->y_mmax)
		return (1);
	if (g->map[tab_y][tab_x] != '1')
		return (0);
	return (1);
}

void	ft_bsh_print(t_game *v, int fx, int fy, unsigned int color)
{
	int	x;
	int	y;

	ft_init_bsh(v, fx, fy);
	x = v->p->x;
	y = v->p->y;
	while (1)
	{
		img_put_pixel(x, y, v, color);
		if ((x == fx && y == fy) || is_new_pos_lavab(v, x, y))
			break ;
		v->e2 = v->er;
		if (v->e2 > -v->dx)
		{
			v->er -= v->dy;
			x += v->sx;
		}
		if (v->e2 < v->dy)
		{
			v->er += v->dx;
			y += v->sy;
		}
	}
}

void	old_pos(t_game *g,int x, int y)
{
	g->old_x = floor(x / g->ts);
	g->old_y = floor(y / g->ts);
}

void	hit_pos(t_game *v, int x, int y)
{
	v->x_intercept = x;
	v->y_intercept = y;
	v->x_wall_pos = floor(x / v->ts);
	v->y_wall_pos = floor(y / v->ts);
	v->distance = sqrt(((x - v->p->x) * (x - v->p->x)) + ((y - v->p->y) * (y - v->p->y)));
}

void	ft_bsh_distance(t_game *v, int fx, int fy)
{
	int	x;
	int	y;

	ft_init_bsh(v, fx, fy);
	x = v->p->x;
	y = v->p->y;
	old_pos(v, x, y);
	while (1)
	{
		if ((x == fx && y == fy) || is_new_pos_lavab(v, x, y))
		{
			hit_pos(v, x, y);
			break ;
		}
		old_pos(v, x, y);
		v->e2 = v->er;
		if (v->e2 > -v->dx)
		{
			v->er -= v->dy;
			x += v->sx;
		}
		if (v->e2 < v->dy)
		{
			v->er += v->dx;
			y += v->sy;
		}
	}
}

void	fov(t_game *g, unsigned int color)
{
	int		x;
	int		y;
	float	lastrad;
	float	firstrad;
	float	step;

	step = (60 * (PI / 180)) / g->wwidth;
	firstrad = g->rad - (step * (g->wwidth / 2));
	lastrad = g->rad + (step * (g->wwidth / 2));
	while (firstrad <= lastrad)
	{
		x = g->p->x - (cos(firstrad) * 1000);
		y = g->p->y - (sin(firstrad) * 1000);
		ft_bsh_print(g, x, y, color);
		firstrad += step;
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
	fov(g, color);
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

unsigned int	color_depth(t_game *g, int r, int gr, int b)
{
	int	color;

	color = 0;
	if (g->c_ray->texture == 'n')
		return (*(unsigned int *)(g->adr_txt + g->off_y * g->t_n->lsz + (g->off_x * (g->t_n->bitsz / 8))));
	if (g->c_ray->texture == 's')
		return (*(unsigned int *)(g->adr_txt + g->off_y * g->t_s->lsz + (g->off_x * (g->t_s->bitsz / 8))));
	if (g->c_ray->texture == 'e')
		return (*(unsigned int *)(g->adr_txt + g->off_y * g->t_e->lsz + (g->off_x * (g->t_e->bitsz / 8))));
	if (g->c_ray->texture == 'w')
		return (*(unsigned int *)(g->adr_txt + g->off_y * g->t_w->lsz + (g->off_x * (g->t_w->bitsz / 8))));
	if (g->c_ray->texture == 0)
	{
		r = 0;
		gr = 0;
		b = 0;
	}
	else
	{
		r = r - (100 * (g->c_ray->distance / g->wheight));
		gr = gr - (100 * (g->c_ray->distance / g->wheight));
		b = b - (100 * (g->c_ray->distance / g->wheight));
	}
	color |= r << 16;
	color |= gr << 8;
	color |= b;
	return ((unsigned int)color);
}

void calculate_offset(t_game *g, int y, int wallheight)
{
	int	distance;

	if (g->c_ray->texture == 'n' || g->c_ray->texture == 's')
		g->off_x = g->c_ray->y_intercept - (g->c_ray->y_wall_pos * g->ts);
	if (g->c_ray->texture == 'e' || g->c_ray->texture == 'w')
		g->off_x = g->c_ray->x_intercept - (g->c_ray->y_wall_pos * g->ts);
	distance = y + (wallheight / 2) - (g->wheight / 2);
	g->off_y = distance * ((float)g->ts / wallheight);
	//printf("off_x %d off_y %d\n", g->off_x, g->off_y);
}

void	draw_ray(t_game *g, int i)
{
	int		y;
	int		y_start;
	int		y_finish;
	float	wall_height;
	float	projection_plane;

	g->c_ray->distance = cos(g->c_ray->radr - g->rad) * g->c_ray->distance;
	projection_plane = ((g->wwidth / 2) / tan((g->fov / 2)));
	wall_height = (g->ts / g->c_ray->distance) * projection_plane;
	y = 0;
	y_start = (g->wheight / 2) - (wall_height / 2);
	y_finish = (g->wheight / 2) + (wall_height / 2);
	while (y < g->wheight)
	{
		if (y < y_start)
			img_put_pixel(i, y, g, g->sky_color);
		if (y >= y_start && y <= y_finish)
		{
			calculate_offset(g, y, wall_height);
			img_put_pixel(i, y, g, color_depth(g, 255, 255, 255));
		}
		if (y > y_finish)
			img_put_pixel(i, y, g, g->ground_color);
		y++;
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

// void	ray_direction(t_ray *ray)
// {
// 	ray->is_ray_up = 0;
// 	ray->is_ray_down = 0;
// 	ray->is_ray_left = 0;
// 	ray->is_ray_right = 0;

// 	if (ray->rad > 0 && ray->rad < PI)
// 		ray->is_ray_up = 1;
// 	else
// 		ray->is_ray_down = 1;
// 	if (ray->rad < (0.5 * PI) || ray->rad > (1.5 * PI))
// 		ray->is_ray_right = 1;
// 	else
// 		ray->is_ray_left = 1;
// }

// void	init_horizontal_wall_hit(t_game *g, t_ray *ray)
// {
// 	ray->hit_horizontal = 0;
// 	ray->x_hor_hit = 0;
// 	ray->y_hor_hit = 0;

// 	ray->y_intercept = floor(g->p->y / g->ts) * g->ts;
// 	if (ray->is_ray_down)
// 		ray->y_intercept += g->ts;
// 	ray->x_intercept = g->p->x + ((ray->y_intercept - g->p->y) / tan(ray->rad));
// 	ray->y_step = g->ts;
// 	if (ray->is_ray_up)
// 		ray->y_step *= -1;
// 	ray->x_step = g->ts / tan(ray->rad);
// 	if (ray->is_ray_left && ray->x_step > 0)
// 		ray->x_step *= -1;
// 	if (ray->is_ray_right && ray->x_step < 0)
// 		ray->x_step *= -1;
// }

// void	horizontal_wall_hit(t_game *g, t_ray *ray)
// {
// 	float	next_x;
// 	float	next_y;

// 	init_horizontal_wall_hit(g, ray);
// 	next_x = ray->x_intercept;
// 	next_y = ray->y_intercept;
// 	while (next_x > 0 && next_y > 0 && next_x < g->x_max && next_y < g->y_max)
// 	{
// 		if (is_new_pos_lavab(g, next_x, next_y - ray->is_ray_up))
// 		{
// 			ray->hit_horizontal = 1;
// 			ray->x_hor_hit = next_x;
// 			ray->y_hor_hit = next_y;
// 			break ;
// 		}
// 		else
// 		{
// 			next_x += ray->x_step;
// 			next_y += ray->y_step;
// 		}
// 	}
// }

// void	init_vertical_wall_hit(t_game *g, t_ray *ray)
// {
// 	ray->hit_vertical = 0;
// 	ray->x_ver_hit = 0;
// 	ray->y_ver_hit = 0;

// 	ray->x_intercept = floor(g->p->x / g->ts) * g->ts;
// 	if (ray->is_ray_right)
// 		ray->x_intercept += g->ts;
// 	ray->y_intercept = g->p->y + ((ray->x_intercept - g->p->x) * tan(ray->rad));
// 	ray->x_step = g->ts;
// 	if (ray->is_ray_left)
// 		ray->x_step *= -1;
// 	ray->y_step = g->ts * tan(ray->rad);
// 	if (ray->is_ray_up && ray->y_step > 0)
// 		ray->y_step *= -1;
// 	if (ray->is_ray_down && ray->y_step < 0)
// 		ray->y_step *= -1;
// }

// // void	vertical_wall_hit(t_game *g, t_ray *ray)
// {
// 	float	next_x;
// 	float	next_y;

// 	init_vertical_wall_hit(g, ray);
// 	next_x = ray->x_intercept;
// 	next_y = ray->y_intercept;
// 	while (next_x >= 0 && next_y >= 0 && next_x <= g->x_max && next_y <= g->y_max)
// 	{
// 		if (is_new_pos_lavab(g, next_x - ray->is_ray_left, next_y))
// 		{
// 			ray->hit_vertical = 1;
// 			ray->x_ver_hit = next_x;
// 			ray->y_ver_hit = next_y;
// 			break ;
// 		}
// 		else
// 		{
// 			next_x += ray->x_step;
// 			next_y += ray->y_step;
// 		}
// 	}
// }

float distance(int x1, int y1, int x2, int y2)
{
	float	distance;

	distance = sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));

	return (distance);
}

// void shortest_distance(t_game *g, t_ray *ray)
// {
// 	float	ver_distance;
// 	float	hor_distance;

// 	if (ray->hit_horizontal == 1)
// 		hor_distance = distance(g->p->x, g->p->y, ray->x_hor_hit, ray->y_hor_hit);
// 	else if (ray->hit_horizontal == 0)
// 		hor_distance = 42424242;
// 	if (ray->hit_vertical == 1)
// 		ver_distance = distance(g->p->x, g->p->y, ray->x_ver_hit, ray->y_ver_hit);
// 	else if (ray->hit_vertical == 0)
// 		ver_distance = 42424242;
// 	if (hor_distance < ver_distance)
// 	{
// 		ray->distance = hor_distance;
// 		ray->hit_vertical = 0;
// 		ray->hit_horizontal = 1;
// 	}
// 	else
// 	{
// 		ray->distance = ver_distance;
// 		ray->hit_vertical = 1;
// 		ray->hit_horizontal = 0;
// 	}
// }

// void texture(t_ray *ray)
// {
// 	ray->texture = 0;
// 	if (ray->hit_horizontal)
// 	{
// 		if (ray->is_ray_up)
// 			ray->texture = 's';
// 		else
// 			ray->texture = 'n';
// 	}
// 	else if (ray->hit_vertical)
// 	{
// 		if (ray->is_ray_left)
// 			ray->texture = 'e';
// 		else
// 			ray->texture = 'w';
// 	}
// }

float	normalise_rad(float rad)
{
	rad = remainder(rad, 2 * PI);
	if (rad < 0)
		rad = (2 * PI) + rad;
	return (rad);
}

// // void ray_distance_projection(t_game *g, t_ray *ray, float rad)
// {
// 	ray->rad = normalise_rad(rad);
// 	ray_direction(ray);
// 	horizontal_wall_hit(g, ray);
// 	vertical_wall_hit(g, ray);
// 	shortest_distance(g, ray);
// 	texture(ray);
// }

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
	g->texture = 0;
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

void load_ray(t_game *g, int id)
{
	t_ray *ray;

	if (id == 0)
		g->c_ray = g->ray;
	ray = g->c_ray;
	ray->distance = g->distance;
	ray->radr = g->radr;
	ray->texture = g->texture;
	ray->old_x = g->old_x;
	ray->old_y = g->old_y;
	ray->x_intercept = g->x_intercept;
	ray->y_intercept = g->y_intercept;
	ray->x_wall_pos = g->x_wall_pos;
	ray->y_wall_pos = g->y_wall_pos;
	g->c_ray = ray->next;
}

void print_rays(t_game *g)
{
	t_ray *ray;

	ray = g->ray;
	while (ray)
	{
		ft_printf("ray id %d  texture %d\n", ray->id, ray->texture);
		ray = ray->next;
	}
}

void	info_texture(t_game *g, int texture)
{
	if (texture == 'n')
		g->adr_txt = mlx_get_data_addr(g->t_n->mlx_xmp, &g->t_n->bitsz,
	 		&g->t_n->lsz, &g->t_n->endi);
	if (texture == 's')
		g->adr_txt = mlx_get_data_addr(g->t_s->mlx_xmp, &g->t_s->bitsz,
	 		&g->t_s->lsz, &g->t_s->endi);
	if (texture == 'e')
		g->adr_txt = mlx_get_data_addr(g->t_e->mlx_xmp, &g->t_e->bitsz,
	 		&g->t_e->lsz, &g->t_e->endi);
	if (texture == 'w')
		g->adr_txt = mlx_get_data_addr(g->t_w->mlx_xmp, &g->t_w->bitsz,
	 		&g->t_w->lsz, &g->t_w->endi);
}

void	ray_draw(t_game *g)
{
	int	last_texture;

	last_texture = 0;
	g->c_ray = g->ray;
	while (g->c_ray)
	{
		if (g->c_ray->texture)
			last_texture = g->c_ray->texture;
		else
			g->c_ray->texture = last_texture;
		info_texture(g, g->c_ray->texture);
		draw_ray(g, g->c_ray->id);
		g->c_ray = g->c_ray->next;
	}
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
	while (id < g->wwidth)
	{
		//ft_printf("here id %d\n", id);
		//ray_distance_projection(g, &g->ray[id], firstrad);
		ft_find_distance(g, firstrad);
		load_ray(g, id);
		//draw_ray(g, id);
		firstrad += step;
		id++;
	}
	ray_draw(g);
	//print_rays(g);
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
	//print_map(g, g->map);
	ray_cast(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	mlx_destroy_image(g->mlx, g->img);
	return (0);
}
