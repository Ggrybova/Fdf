/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 14:44:31 by ggrybova          #+#    #+#             */
/*   Updated: 2017/06/07 15:18:55 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			*ft_color(char *str)
{
	int		*rgb;
	char	*tmp;
	int		i;
	int		k;
	int		*res;

	k = -1;
	rgb = (int *)malloc(sizeof(int) * 2);
	res = (int *)malloc(sizeof(int) * 4);
	while (++k <= 3 && (i = -1) < 0)
	{
		tmp = ft_strdup(str + 2);
		str = ft_strdup(tmp);
		while (++i < 2 && (rgb[i] = 0) > -1)
		{
			if (tmp[i] >= 65 && tmp[i] <= 70)
				rgb[i] = (int)tmp[i] - 55;
			else if (tmp[i] >= 97 && tmp[i] <= 102)
				rgb[i] = (int)tmp[i] - 87;
			else if (tmp[i] >= 48 && tmp[i] <= 57)
				rgb[i] = (int)tmp[i] - 48;
		}
		res[k] = rgb[0] * 16 + rgb[1];
	}
	return (res);
}

float		*line_color(int *c1, int *c2, float h)
{
	float	*del;
	int		i;

	i = -1;
	del = (float *)malloc(sizeof(float) * 4);
	while (++i < 4)
		del[i] = (c2[i] - c1[i]) / h;
	return (del);
}

int			*start_color(int *color1)
{
	int		*k;

	k = (int *)malloc(sizeof(int) * 4);
	k[0] = color1[0];
	k[1] = color1[1];
	k[2] = color1[2];
	k[3] = color1[3];
	return (k);
}

int			*grad(int *color1, int *c, float *del, int n)
{
	color1[0] = c[0] + (del[0] * n);
	color1[1] = c[1] + (del[1] * n);
	color1[2] = c[2] + (del[2] * n);
	color1[3] = c[3] + (del[3] * n);
	return (color1);
}
