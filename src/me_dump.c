/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_dump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 10:27:02 by pribault          #+#    #+#             */
/*   Updated: 2017/06/08 17:02:43 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_editor.h"

void	dump_entities(t_map *map)
{
	t_entity	*entity;
	t_list		*list;
	t_uint		i;

	list = map->entities;
	i = 0;
	if (map->entities)
		ft_putendl("___ entities ___\n");
	while (list)
	{
		entity = (t_entity*)list->content;
		ft_printf(" - %u entity %u at %d:%d vue=%d\n", i, entity->id,
		(int)entity->pos.x + 1, (int)entity->pos.y + 1,
		(int)((entity->angle * 360) / (2 * PI)));
		i++;
		list = list->next;
	}
}

char	map_dump(t_map *map, char **instruct)
{
	int		i;
	int		j;

	if (!map->magic)
		return (ft_error(4));
	instruct++;
	dump_entities(map);
	ft_printf("\n     ", (j = 0));
	while (j < map->w)
		ft_printf("%.2d ", ++j);
	ft_putchar('\n');
	i = 0;
	while (i < map->h)
	{
		j = 0;
		ft_printf("%.3d  ", i + 1);
		while (j < map->w)
		{
			ft_printf("\033[38;5;%dm%.2x ", map->map[i][j], map->map[i][j]);
			j++;
		}
		ft_putstr("\n\033[0m");
		i++;
	}
	return (0);
}
