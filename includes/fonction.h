/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:56:30 by rpol              #+#    #+#             */
/*   Updated: 2023/02/01 19:56:34 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONCTION_H
# define FONCTION_H

void		parse_error(void);
char		*parse(t_game *game);
void		final_map(t_game *game);
void		parse_settings(t_game *game);
void		is_collunm_top(t_game *game);
void		is_collunm_bot(t_game *game);
void		is_line_left(t_game *game);
void		is_line_right(t_game *game);
void		if_zero(t_game *game, char **tab3);
void		is_player(t_game *game);
void		main_parsing(t_game *game);
void		add_border(t_game *game);
void		throw_error(t_game *game, char *tab);
void		throw_error2(t_game *game);
void		throw_error3(t_game *game, char *tab);
void		throw_error4(t_game *game);
void		throw_error66(t_game *game);
void		free_magic(t_game *g);
void		free_help(char *str, char *compas, char *compas2);
void		free_tab(char **tab);
char		*ft_strjoin4(char const *s1, char const *s2);
int			ft_isnum(char *str);
char		*ft_strldup(char *source, int size);
int			ft_strcmp(const char *s1, const char *s2);
int			find_longer_line(char	**map);
int			find_longer_collum(char	**map);
void		throw_error5(t_game *g);
void		leave(t_game *game, char *str, char *compas, char *compas2);
void		fail_finish(t_game *g);
void		free_magic(t_game *g);
void		parse_error(void);
int			parse_rgb_color(t_game *game, char *s);
void		parse_help(t_game *game, char *str);
void		parse_help2(t_game *game, char *str);
void		parse_help3(t_game *game, char *str);
void		parse_help4(t_game *game, char *str);
void		parse_help5(t_game *game, char *str);
void		parse_help6(t_game *game, char *str);
char		*make_str(t_game *game, int i);

/* SRCS/MAIN.C */

void		is_cub(int ac, char **av);

void		is_xpm(t_game *g, char *xpm);

void		init_game(t_game *g, char *file);

void		finish(t_game *g);

/* SRCS/DISPLAY/PLAYER_INIT.C */

void		mlx_fail_exit(t_game *g);

int			ft_tablen(char **tab);

void		init_player_param(t_game *g);

float		where_is_player_facing(char direction);

void		init_player_position(t_game *g, char **tab);

/* SRCS/DISPLAY/TEXTURES.C */

void		destroy_images_texture(t_game *g);

void		*texture_init(t_game *g, char *path_texture);

void		init_textures(t_game *g);

void		info_texture(t_game *g, int texture);

void		calculate_texture(t_game *g);

/* SRCS/DISPLAY/DISPLAY.C */

void		ft_init_bsh(t_game *g, int fx, int fy);

void		old_pos(t_game *g, int x, int y);

void		hit_pos(t_game *g, int x, int y);

void		ft_bsh_distance(t_game *g, int fx, int fy);

int			render(t_game *g);

/* SRCS/DISPLAY/RAY_CASTING.C */

void		calculate_offset(t_game *g, int y, int wallheight);

int			is_new_pos_lavab(t_game *g, float x, float y);

int			is_new_pos_lava(t_game *g, int x, int y);

void		ft_find_distance(t_game *g, float rad);

void		ray_cast(t_game *g);

/* SRCS/DISPLAY/PIXEL_PUTS.C */

int			img_put_pixel(int x, int y, t_game *g, unsigned int color);

void		color_the_sky_and_the_ground(t_game *g, int i, int y_s, int y_g);

void		txt_to_img_pixel_put(t_game *g, int i, int y_start);

void		rectangle_window_size(t_game *g, unsigned int color);

void		draw_ray(t_game *g, int i);

/* SRCS/DISPLAY/I_LIKE_TO_MOVE_IT.C */

int			key_released(int keycode, t_game *game);

int			key_pressed(int keycode, t_game *game);

int			is_new_pos_lava_move(t_game *g, float x, float y);

float		normalise_rad(float rad);

void		update_player(t_game *g);

/* SRCS/DISPLAY/MINI_MAP.C */

void		ft_bsh_print(t_game *g, int fx, int fy);

void		player_render(t_game *g, unsigned int color);

int			minimap_move(t_game *g, int x, int y, int i);

void		rectangle_tilesize(t_game *g, int x_s, int y_s, unsigned int color);

void		print_map(t_game *g, char **tab);

#endif