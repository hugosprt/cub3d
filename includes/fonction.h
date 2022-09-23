#ifndef FONCTION_H
# define FONCTION_H


/* MAIN.C.C */

void    parse_error();
void    parse(char *file, t_game *game);

/* DISPLAY.C */

void	init_img(t_game *g, char **tab);

void	finish(t_game *g, char **tab);

void	print_tiles(t_game *a, char **tab);

/* I_LIKE_TO_MOVE_IT.C */

void	move_up(t_game *root, int n);

void	move_right(t_game *root, int n);

void	rotate(t_game *root, int n);				



#endif