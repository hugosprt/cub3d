#ifndef FONCTION_H
# define FONCTION_H

void		parse_error(void);
char		*parse(t_game *game);
void		struct_init(t_game *game, char *file);
void		final_map(t_game *game);
int			add_value(t_game *game, char *str);
void		parse_settings(t_game *game);
void		is_collunm_top(t_game *game);
void		is_collunm_bot(t_game *game);
void		is_line_left(t_game *game);
void		is_line_right(t_game *game);
void		if_zero(t_game *game, char **tab3);
void		is_player(t_game *game);
void		main_parsing(t_game *game);
void		print_map2(t_game *game);
void		add_border(t_game *game);
void		throw_error(t_game *game, char *tab);
void		throw_error2(t_game *game, char *tab);
void		throw_error3(t_game *game, char *tab);
void		throw_error4(t_game *game);
void		throw_error66(t_game *game);
void		free_magic(t_game *g);
void		free_tab(char **tab);
char		*ft_strjoin4(char const *s1, char const *s2);
int			ft_isnum(char *str);
char		*ft_strldup(char *source, int size);
int			ft_strcmp(const char *s1, const char *s2);
int			find_longer_line(char	**map);
int			find_longer_collum(char	**map);
/* MAIN.C.C */
void		fail_finish(t_game *g);
void		free_magic(t_game *g);
void		parse_error(void);
int			parse_rgb_color(t_game *game, char *s);
/* DISPLAY.C */
int		ft_tablen(char **tab);

int		is_new_pos_lava(t_game *g, int x, int y);

void	init_game(t_game *g, char *file);

void	finish(t_game *g);

void	print_tiles(t_game *a, char **tab);

int		render(t_game *g);

/* I_LIKE_TO_MOVE_IT.C */

void	update_player(t_game *g);


int	is_new_pos_lava_move(t_game *g, float x, float y);
void		init_game(t_game *g, char *file);
void		finish(t_game *g);
void		print_tiles(t_game *a, char **tab);
int			render(t_game *g);
/* I_LIKE_TO_MOVE_IT.C */
void		update_player(t_game *g);

#endif