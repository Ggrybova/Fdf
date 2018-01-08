/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 12:40:53 by ggrybova          #+#    #+#             */
/*   Updated: 2017/06/08 13:00:07 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_FDF_H
# define FDF_FDF_H
# define WIDTH 1600
# define HEIGHT 1200
# define PI 3.141592

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"
# include <math.h>

typedef	struct		s_coord
{
	float			x;
	float			y;
	float			z;
	char			*col;
	int				i;
}					t_coord;

typedef	struct		s_rotation
{
	float			a1;
	float			a2;
	float			a3;
}					t_rotation;

typedef struct		s_mlx
{
	float			m;
	float			n;
	float			size;
	float			c_x;
	float			c_y;
	float			*cx_h;
	float			*cy_h;
	float			*cx_v;
	float			*cy_v;
	float			k;
	t_rotation		*an;

	t_coord			**data;
	void			*mlx;
	void			*win;
	void			*im;
	char			*addr;
	int				b_p_p;
	int				size_l;
	int				end;
	int				fd;
	float			*s;
	int				i;
}					t_mlx;

void				read_map(t_mlx *map, const char *filename);
void				create_map(t_mlx *map);
void				ft_print_map(t_mlx *map);
int					*ft_color(char *str);
float				*line_color(int *c1, int *c2, float h);
int					*start_color(int *color1);
int					*grad(int *color1, int *c, float *del, int n);
int					ft_hook(int key);
int					ft_hook_rotation(int key, t_mlx *map);
void				rotation_ox(t_mlx *m, int key);
void				rotation_oy(t_mlx *m, int key);
void				rotation_oz(t_mlx *m, int key);
void				zum(t_mlx *m, int key);

void				*mlx_init();

#endif
