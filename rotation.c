/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 14:37:10 by ggrybova          #+#    #+#             */
/*   Updated: 2017/06/07 17:55:50 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		rotation_ox(t_mlx *m, int key)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	k = -1;
	(m->an)->a1 = (key == 126) ? (m->an)->a1 + PI / 30 : (m->an)->a1 - PI / 30;
	while (++i < m->m && (j = -1) >= -1)
	{
		while (++j < m->n && ++k >= 0)
		{
			m->data[k]->x = m->cx_h[j] + (i - m->c_x) * m->k *
				sinf((m->an)->a1);
			m->data[k]->y = m->cy_h[j] - (i - m->c_x) * m->k *
				cosf((m->an)->a1);
			m->cx_v[i] = (k - i * m->n == m->c_y) ? m->data[k]->x : m->cx_v[i];
			m->cy_v[i] = (k - i * m->n == m->c_y) ? m->data[k]->y : m->cy_v[i];
			(m->data)[k]->x = (m->data)[k]->x + (m->data)[k]->z * sinf(PI / 2 -
			(m->an)->a1) + (m->data)[k]->z * cosf(PI - (m->an)->a2);
			(m->data)[k]->y = (m->data)[k]->y - (m->data)[k]->z * cosf(PI +
			(m->an)->a1) + (m->data)[k]->z * sinf(PI / 2 + (m->an)->a2);
		}
	}
}

void		rotation_oy(t_mlx *m, int key)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	k = -1;
	(m->an)->a2 = (key == 123) ? (m->an)->a2 + PI / 30 : (m->an)->a2 - PI / 30;
	while (++i < m->m && (j = -1) >= -1)
	{
		while (++j < m->n && ++k >= 0)
		{
			(m->data)[k]->x = m->cx_v[i] + (j - m->c_y) * m->k *
				cosf((m->an)->a2);
			(m->data)[k]->y = m->cy_v[i] + (j - m->c_y) * m->k *
				sinf((m->an)->a2);
			m->cx_h[j] = (k >= m->c_x * m->n && k < (m->c_x + 1) * m->n) ?
				(m->data)[k]->x : m->cx_h[j];
			m->cy_h[j] = (k >= m->c_x * m->n && k < (m->c_x + 1) * m->n) ?
				(m->data)[k]->y : m->cy_h[j];
			(m->data)[k]->x = (m->data)[k]->x + (m->data)[k]->z * cosf(PI -
					(m->an)->a2) + (m->data)[k]->z * sinf(PI / 2 - (m->an)->a1);
			(m->data)[k]->y = (m->data)[k]->y + (m->data)[k]->z * sinf(PI / 2
					+ (m->an)->a2) - (m->data)[k]->z * cosf(PI + (m->an)->a1);
		}
	}
}

void		rotation_oz(t_mlx *m, int key)
{
	if (key == 83)
	{
		rotation_ox(m, 126);
		rotation_oy(m, 123);
	}
	else
	{
		rotation_ox(m, 125);
		rotation_oy(m, 124);
	}
}

void		zum(t_mlx *m, int key)
{
	float	p;
	float	r;

	r = (key == 69) ? 2 : -2;
	if (m->k - 3 >= 1)
	{
		p = -1;
		while (++p < m->n)
		{
			m->cx_h[(int)p] = m->cx_h[(int)p] / m->k * (m->k + r);
			m->cy_h[(int)p] = m->cy_h[(int)p] / m->k * (m->k + r);
		}
		p = -1;
		while (++p < m->m)
		{
			m->cx_v[(int)p] = m->cx_v[(int)p] / m->k * (m->k + r);
			m->cy_v[(int)p] = m->cy_v[(int)p] / m->k * (m->k + r);
		}
		m->k = m->k + r;
		rotation_ox(m, 126);
		rotation_ox(m, 125);
	}
}
