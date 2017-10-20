/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_edit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 10:27:02 by pribault          #+#    #+#             */
/*   Updated: 2017/06/12 11:51:18 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_editor.h"

int		set_y(t_point a, t_point b, t_point i)
{
	int		y;

	if (b.x != a.x)
		y = (i.x < b.x) ? a.y + ((i.x - a.x + 1) * (b.y - a.y)) / (b.x - a.x) :
	a.y + ((i.x - a.x - 1) * (b.y - a.y)) / (b.x - a.x);
	y = (i.x == b.x) ? b.y : y;
	return (y);
}

char	map_set_line(t_map *map, char **instruct)
{
	t_uchar	block;
	t_point	a;
	t_point	b;
	t_point	i;
	int		y;

	if (!map->magic)
		return (ft_error(4));
	a.x = ft_atoi(instruct[1]);
	a.y = ft_atoi(instruct[2]);
	b.x = ft_atoi(instruct[3]);
	b.y = ft_atoi(instruct[4]);
	block = ft_atoi(instruct[5]);
	i = a;
	while ((a.x < b.x) ? i.x <= b.x : i.x >= b.x)
	{
		y = set_y(a, b, i);
		if (i.x > 0 && i.y > 0 && i.x <= map->w && i.y <= map->h)
			map->map[i.y - 1][i.x - 1] = block;
		if ((i.y < y) ? i.y < y - 1 : i.y > y + 1)
			i.y += (i.y < y) ? 1 : -1;
		else
			i.x += (a.x < b.x) ? 1 : -1;
	}
	return (0);
}

char	map_set_block(t_map *map, char **instruct)
{
	int		x;
	int		y;

	if (!map->magic)
		return (ft_error(4));
	x = ft_atoi(instruct[1]);
	y = ft_atoi(instruct[2]);
	if (x > 0 && y > 0 && x <= map->w && y <= map->h)
		map->map[y - 1][x - 1] = ft_atoi(instruct[3]);
	else
		ft_printf("position of block is out of the map !\n");
	return (0);
}
