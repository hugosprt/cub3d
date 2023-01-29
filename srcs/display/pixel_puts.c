/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_puts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:55:35 by rpol              #+#    #+#             */
/*   Updated: 2023/01/30 00:31:53 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	img_put_pixel(int x, int y, t_game *g, unsigned int color)
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

void	color_the_sky_and_the_ground(t_game *g, int i, int y_s, int y_g)
{
	int	y;

	y = 0;
	while (y < g->wheight)
	{
		if (y < y_s)
			img_put_pixel(i, y, g, g->sky_color);
		if (y >= y_g)
			img_put_pixel(i, y, g, g->ground_color);
		y++;
	}
}

void	txt_to_img_pixel_put(t_game *g, int i, int y_start)
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
