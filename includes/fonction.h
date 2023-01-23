#ifndef FONCTION_H
# define FONCTION_H

void    parse_error();
char    *parse(t_game *game);
void	struct_init(t_game *game, char *file);

char **add_border(t_game *game);
int add_value(t_game *game, char *str);
void parse_settings(t_game *game);
char	**final_map(t_game *game);
void is_collunm_top(t_game *game);
void is_collunm_bot(t_game *game);
void	is_line_left(t_game *game);
void	is_line_right(t_game *game);
void	if_zero(t_game *game);
void	is_player(t_game *game);
#endif