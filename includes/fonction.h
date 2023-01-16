#ifndef FONCTION_H
# define FONCTION_H

void    parse_error();
char    *parse(t_game *game);
void	struct_init(t_game *game, char *file);

char **add_border(t_game *game);
int add_value(t_game *game, char *str);
#endif