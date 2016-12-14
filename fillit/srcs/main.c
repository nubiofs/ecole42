/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmasiala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 09:18:18 by fmasiala          #+#    #+#             */
/*   Updated: 2016/12/13 11:56:33 by fmasiala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int		main(int argc, char **argv)
{
	char	*map;
	int		width;
	int		nbr_tetri;
	t_tetri **tetris;

	nbr_tetri = 0;
	width = 2;
	tetris = reader(argc, argv[1], &nbr_tetri);
	while (1)
	{
		map = ft_getmap(width);
		if (!map)
			return (0);
		if (ft_write_all_tetriminos(map, width, tetris, nbr_tetri, 0, 0))
		{
			if ((empty_map(map)) != 0)
				return (1);
			ft_putstr(map);
			return (0);
		}
		ft_strclr(map);
		width++;
	}
	return (1);
}
