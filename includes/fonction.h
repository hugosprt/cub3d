#ifndef FONCTION_H
# define FONCTION_H

/* MAIN.C.C */

void	parse_error(void);

void	parse(char *file, t_game *game);

/* DISPLAY.C */

void	init_game(t_game *g);

void	finish(t_game *g);

void	print_tiles(t_game *a, char **tab);

int		render(t_game *g);

/* I_LIKE_TO_MOVE_IT.C */

void	update_player(t_game *g);

int		is_new_pos_lava(t_game *g, float x, float y);

#endif