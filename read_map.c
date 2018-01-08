/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 09:49:23 by ggrybova          #+#    #+#             */
/*   Updated: 2017/06/07 17:24:36 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float		*size_map(int fd)
{
	char	**l;
	float	*m;
	char	**a;

	m = ft_memalloc(4);
	m[3] = 0;
	m[2] = 0;
	l = (char **)malloc(sizeof(char *));
	if (fd == -1)
	{
		ft_putstr("Cannot open file\n");
		exit(0);
	}
	while (get_next_line(fd, l) > 0)
	{
		m[1] = 0;
		a = ft_strsplit(*l, ' ');
		while (*a != NULL && a++ && (m[2]++) >= 0)
			m[1]++;
		m[0]++;
		ft_strdel(a);
		m[3] = fmaxf((m[1]), m[3]);
	}
	return (m);
}

void		fill_data(t_mlx *map)
{
	map->an = (t_rotation *)malloc(sizeof(t_rotation));
	(map->an)->a1 = PI / 2;
	(map->an)->a2 = PI / 2;
	(map->an)->a3 = 0;
	map->m = map->s[0];
	map->n = map->s[1];
	map->size = map->s[2];
	map->c_x = (int)(map->m / 2);
	map->c_y = (int)(map->n / 2);
	map->cx_h = (float *)malloc(sizeof(float) * (int)map->n);
	map->cy_h = (float *)malloc(sizeof(float) * (int)map->n);
	map->cx_v = (float *)malloc(sizeof(float) * (int)map->m);
	map->cy_v = (float *)malloc(sizeof(float) * (int)map->m);
}

int			valid_col(char *s)
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	if ((ft_strlen(s)) > 3 && (ft_strlen(s)) < 11)
		if (s[i] == '0')
			if (s[++i] == 'x')
				while (s[++i])
					if ((s[i] > 47 && s[i] < 58) || (s[i] > 64 && s[i] < 71)
						|| (s[i] > 96 && s[i] < 103))
						j++;
	if (j < 2 || j > 8 || i - j != 2)
	{
		ft_putstr("No valid map\n");
		exit(0);
	}
	return (1);
}

void		fill_coord(t_mlx *map, float x, float y, char *str)
{
	map->i++;
	(map->data)[map->i] = (t_coord *)malloc(sizeof(t_coord));
	(map->data)[map->i]->col = (char *)malloc(sizeof(char) * 12);
	if (ft_strchr(str, ',') == NULL)
	{
		(map->data)[map->i]->z = ft_atoi(str);
		(map->data)[map->i]->col = ft_strdup("0xFF69B4");
	}
	else
	{
		(map->data)[map->i]->z = ft_atoi(ft_strsub(str, 0, ft_strlen(str)
					- ft_strlen(ft_strchr(str, ','))));
		(map->data)[map->i]->col = ft_strdup(ft_strchr(str, ',') + 1);
		valid_col((map->data)[map->i]->col);
	}
	(map->data)[map->i]->x = x;
	(map->data)[map->i]->y = y;
	if (x == map->c_x || y == map->c_y)
	{
		map->cx_h[(int)y] = (x == map->c_x) ? x : map->cx_h[(int)y];
		map->cy_h[(int)y] = (x == map->c_x) ? y : map->cy_h[(int)y];
		map->cx_v[(int)x] = (y == map->c_y) ? x : map->cx_v[(int)x];
		map->cy_v[(int)x] = (y == map->c_y) ? y : map->cy_v[(int)x];
	}
}

void		read_map(t_mlx *map, const char *filename)
{
	char	**line;
	float	*num;
	char	**ar;

	num = (float *)malloc(sizeof(float) * 3);
	line = (char **)malloc(sizeof(char *));
	map->fd = open(filename, O_RDONLY);
	map->s = (size_map(map->fd));
	fill_data(map);
	map->data = (t_coord **)malloc(sizeof(t_coord *) * (int)map->size);
	num[2] = 0;
	close(map->fd);
	map->fd = open(filename, O_RDONLY);
	map->i = -1;
	while (get_next_line(map->fd, line) > 0)
	{
		num[1] = -1;
		ar = ft_strsplit(*line, ' ');
		while (*ar != NULL && ++(num[2]))
			fill_coord(map, num[0], (++num[1]), *ar++);
		num[0]++;
		ft_strdel(ar);
	}
}
