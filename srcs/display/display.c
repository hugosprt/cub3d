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

void	ft_bsh(t_game *v, int fx, int fy, unsigned int color)
{
	int	x;
	int	y;

	ft_init_bsh(v, fx, fy);
	x = v->p->x;
	y = v->p->y;
	while (1)
	{
		img_put_pixel(x, y, v, color);
		if ((x == fx && y == fy) || is_new_pos_lava(v, x, y))
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
		ft_bsh(g, x, y, color);
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

void	print_tiles(t_game *g, char **tab)
{
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
			if (tab[g->y][g->x] == 'N')
			{
				tab[g->y][g->x] = '0';
				rectangle_tilesize(g, 0x000000FF);
				g->p->x = (g->x * g->ts) + (g->ts / 2);
				g->p->y = (g->y * g->ts) + (g->ts / 2);
				g->p->i = 1;
				g->p->a = 90;
				ft_printf("player posi_x%d___new_y%d\n", g->p->x, g->p->y);
				ft_printf("player angle%d\n", g->p->a);
				g->rad = (90 * (PI / 180));
			}
		}
	}
	player_render(g, 0x00FF0000);
}

int	render(t_game *g)
{
	if (g->step == 0 && g->side == 0 && g->turn == 0 && g->p->i > 0)
		return (0);
	else if (g->p->i > 0)
		update_player(g);
	g->img = mlx_new_image(g->mlx, g->wwidth, g->wheight);
	if (!g->img)
		return (ft_putstr_fd("Error\n", 2), 1);
	g->adr = mlx_get_data_addr(g->img, &g->bitsz, &g->lsz, &g->endi);
	print_tiles(g, g->tab);
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	mlx_destroy_image(g->mlx, g->img);
	return (0);
}
