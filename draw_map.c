/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 10:28:12 by ggrybova          #+#    #+#             */
/*   Updated: 2017/06/08 12:59:46 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			draw_pixel_10(t_mlx *m, float x, float y, int *color)
{
	int		i;
	float	h;
	float	w;

	w = WIDTH;
	h = HEIGHT;
	i = (int)(4 * w * (int)(x + (h - m->k * m->m) / 2) + 4 * (int)(y +
				(w - m->k * m->n) / 2));
	if (i >= 0 && i < 4 * w * h && (int)(y + (w - m->k * m->n) / 2) > 0 &&
			(int)(y + (w - m->k * m->n) / 2) < WIDTH)
	{
		m->addr[i] = (char)color[2];
		m->addr[i + 1] = (char)color[1];
		m->addr[i + 2] = (char)color[0];
		m->addr[i + 3] = (char)color[3];
	}
	return (i);
}

float		*coord(t_mlx *m, int j, int k)
{
	float	*coord;

	coord = (float *)malloc(sizeof(float) * 4);
	coord[0] = (m->data)[j]->x;
	coord[1] = (m->data)[j]->y;
	coord[2] = (m->data)[k]->x;
	coord[3] = (m->data)[k]->y;
	return (coord);
}

float		*x_y(float *cxy)
{
	float	*xy;

	xy = (float *)malloc(sizeof(float) * 2);
	if (fabsf(cxy[2] - cxy[0]) >= fabsf(cxy[3] - cxy[1]))
		xy[0] = cxy[0];
	else
		xy[1] = cxy[1];
	return (xy);
}

void		draw_line(t_mlx *m, int j, int k, int *color1)
{
	float	*xy;
	float	*del;
	int		n;
	int		*c;
	float	*cxy;

	n = -1;
	c = start_color(color1);
	del = line_color(color1, ft_color((m->data)[k]->col), 1000);
	cxy = coord(m, j, k);
	xy = x_y(cxy);
	while (++n < 999)
	{
		if (fabsf(cxy[2] - cxy[0]) >= fabsf(cxy[3] - cxy[1]))
			xy[1] = (cxy[3] - cxy[1]) / (cxy[2] - cxy[0]) * xy[0] + cxy[1]
			- (cxy[3] - cxy[1]) / (cxy[2] - cxy[0]) * cxy[0];
		else
			xy[0] = (cxy[2] - cxy[0]) / (cxy[3] - cxy[1]) * xy[1] + cxy[0]
			- (cxy[2] - cxy[0]) / (cxy[3] - cxy[1]) * cxy[1];
		draw_pixel_10(m, (int)xy[0], (int)xy[1], color1);
		color1 = grad(color1, c, del, n);
		xy[1] = xy[1] + (cxy[3] - cxy[1]) / 1000;
		xy[0] = xy[0] + (cxy[2] - cxy[0]) / 1000;
	}
}

void		ft_print_map(t_mlx *m)
{
	int		j;

	m->im = mlx_new_image(m->mlx, WIDTH, HEIGHT);
	m->addr = mlx_get_data_addr(m->im, &(m->b_p_p), &(m->size_l), &(m->end));
	j = -1;
	while (++j >= 0 && j + 1 < m->s[2])
	{
		if (m->k == 1)
			draw_pixel_10(m, (int)(m->data)[j]->x, (int)(m->data)[j]->y,
			ft_color((m->data)[j]->col));
		else
		{
			if ((j + 1) % (int)(m->s[1]) != 0)
				draw_line(m, j, j + 1, ft_color((m->data)[j]->col));
			if (j + (int)m->s[1] < (int)m->s[2])
				draw_line(m, j, j + (int)m->s[1], ft_color((m->data)[j]->col));
		}
	}
	mlx_put_image_to_window(m->mlx, m->win, m->im, 10, 10);
	mlx_destroy_image(m->mlx, m->im);
}
