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
void main_parsing(t_game *game); 
void print_map2(t_game *game);
/* MAIN.C.C */

void	parse_error(void);

/* DISPLAY.C */

void	init_game(t_game *g, char *file);

void	finish(t_game *g);

void	print_tiles(t_game *a, char **tab);

int		render(t_game *g);

/* I_LIKE_TO_MOVE_IT.C */

void	update_player(t_game *g);

int		is_new_pos_lava(t_game *g, float x, float y);


#endif