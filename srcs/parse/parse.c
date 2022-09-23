#include "../../includes/cub.h"

void    parse(char *file, t_game *game)
{
    int     fd;
    //char    *line;

    if (ft_strlen(file) < 5)
        parse_error();
    fd = open(file, O_RDONLY);
    if (fd == -1)
        parse_error();
    game->ground_color = 0;
    game->sky_color = 0;
    game->size = 3;
   // parse_game(fd, &line, game);
}

// void    parse_game(int fd, char **line, t_game *game)
// {
//     int s;

//     game->ground_color = 0;
//     game->sky_color = 0;
//     s = get_next_line(fd);
//     while (s >= 0)
//     {
//         if (**line != '\0')
//             return ;
//         free(*line);
//         s = get_next_line(fd);
//     }
// }