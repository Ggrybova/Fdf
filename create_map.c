/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:12:37 by ggrybova          #+#    #+#             */
/*   Updated: 2017/06/07 17:48:21 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			ft_hook(int key)
{
	if (key == 53)
		exit(1);
	return (1);
}

int			ft_hook_rotation(int key, t_mlx *map)
{
	int		i;

	if (key == 126 || key == 125)
		rotation_ox(map, key);
	else if (key == 123 || key == 124)
		rotation_oy(map, key);
	else if ((key == 88 || key == 85) && (i = -1) < map->size)
	{
		while (++i < map->size)
			if (map->data[i]->z != 0)
				map->data[i]->z = (key == 88) ? map->data[i]->z + 31.1 :
					map->data[i]->z - 31.1;
		rotation_ox(map, 126);
		rotation_ox(map, 125);
	}
	else if (key == 84 || key == 83)
		rotation_oz(map, key);
	else if (key == 69)
		zum(map, key);
	else if (key == 78)
		zum(map, key);
	ft_print_map(map);
	return (1);
}

void		create_map(t_mlx *m)
{
	float	i;

	i = -1;
	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, (WIDTH), (HEIGHT), "FDF");
	while (++i < m->n && (m->k = (int)(fminf(HEIGHT, WIDTH) /
			fmaxf((int)(m->m * 1.8), (int)(m->n * 1.8)))) > 0)
	{
		m->cx_h[(int)i] = m->cx_h[(int)i] * m->k;
		m->cy_h[(int)i] = m->cy_h[(int)i] * m->k;
	}
	while (--i > -1)
	{
		m->cx_v[(int)i] = m->cx_v[(int)i] * m->k;
		m->cy_v[(int)i] = m->cy_v[(int)i] * m->k;
	}
	if (m->k < 1)
	{
		ft_putstr("Change size of window\n");
		exit(0);
	}
	ft_hook_rotation(126, m);
	mlx_hook(m->win, 2, 5, ft_hook, NULL);
	mlx_key_hook(m->win, ft_hook_rotation, m);
	mlx_loop(m->mlx);
}
