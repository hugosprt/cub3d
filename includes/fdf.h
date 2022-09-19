/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:16:22 by rpol              #+#    #+#             */
/*   Updated: 2022/09/19 10:57:04 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "mlx.h"
# include "libft.h"
# include <math.h>

typedef struct s_map {
	int				x;
	int				rx;
	int				y;
	int				ry;
	int				z;
	int				c;
	struct s_map	*next;
}				t_map;

typedef struct s_tab {
	char			*s;
	struct s_tab	*next;
}				t_tab;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	void	*img;
	int		lsz;
	int		bitsz;
	int		endi;
	char	*adr;
	int		size;
	char	*name;
	int		fd;
	int		winx;
	int		winy;
	t_tab	*tab;
	t_tab	*l;
	char	*s;
	int		err;
	int		posx;
	int		posy;
	int		a;
	int		stdc;
	int		cc;
	double	alt;
	int		zoom;
	int		movex;
	int		movey;
	int		dy;
	int		dx;
	int		sx;
	int		sy;
	int		er;
	int		e2;
	t_map	*m3;
	t_map	*topl;
}				t_vars;

/*IN FT_DRAW.C*/

int		ft_draw(t_vars *vars);

/*IN FDF.C*/

void	ft_destroy(t_vars *vars);

int		fput(char *s);

/*IN FT_PARSING.C*/

void	ft_init_bsh(t_vars *vars, t_map *m0, t_map *m1);

int		ft_atoip(t_vars *vars, int sign, int nb);

int		ft_parsing(int ac, char **av, t_vars *vars);

/*IN GET_NEXT_LINE.C*/

char	*get_next_line(int fd, t_vars *vars);

int		gnl(t_vars *vars);

/*IN GET_NEXT_LINE_UTILS.C*/

int		ft_strchr(char *s, char c);

int		ft_strlen(char *s);

char	*ft_strjoin(char *s1, char *s2);

char	*ft_line(char *s);

char	*ft_cut(char *s, char *line);

/* ft_linkinit.c */

void	ft_freelka(t_vars *v);

void	ft_freelk(t_vars *vars);

int		ft_linkinit(t_vars *vars);

#endif