/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:31:38 by rpol              #+#    #+#             */
/*   Updated: 2023/02/01 16:17:24 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	destroy_images_texture(t_game *g)
{
	if (g->t_n != NULL)
		mlx_destroy_image(g->mlx, g->t_n);
	if (g->t_s != NULL)
		mlx_destroy_image(g->mlx, g->t_s);
	if (g->t_e != NULL)
		mlx_destroy_image(g->mlx, g->t_e);
	if (g->t_w != NULL)
		mlx_destroy_image(g->mlx, g->t_w);
}

void	*texture_init(t_game *g, char *path_texture)
{
	int		t;
	int		t1;
	void	*txt;

	is_xpm(g, path_texture);
	t = g->ts;
	txt = mlx_xpm_file_to_image(g->mlx, path_texture, &t, &t1);
	if (t != g->ts || t1 != g->ts)
	{
		ft_printf("Stop this right now and give me good texture\n");
		finish(g);
	}
	if (!txt)
	{
		ft_printf("Stop this right now and give me good texture\n");
		finish(g);
	}
	return (txt);
}

void	init_textures(t_game *g)
{
	g->t_n = texture_init(g, g->no_texture);
	g->t_s = texture_init(g, g->so_texture);
	g->t_e = texture_init(g, g->ea_texture);
	g->t_w = texture_init(g, g->we_texture);
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
