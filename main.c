/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 10:57:54 by ggrybova          #+#    #+#             */
/*   Updated: 2017/06/07 16:56:44 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			main(int argc, char **argv)
{
	t_mlx	*map;

	if (argc != 2)
	{
		ft_putstr("usage: ./fdf map_file\n");
		exit(0);
	}
	map = (t_mlx *)malloc(sizeof(t_mlx));
	read_map(map, argv[1]);
	create_map(map);
	return (1);
}
