/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 10:27:02 by pribault          #+#    #+#             */
/*   Updated: 2017/05/29 12:03:02 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_editor.h"

char	map_create(t_map *map, char **instruct)
{
	int		i;

	i = 0;
	if (map->magic)
		map_unload(map, NULL);
	map->magic = MAGIC;
	map->name = ft_strdup(instruct[1]);
	map->w = ft_atoi(instruct[2]);
	map->h = ft_atoi(instruct[3]);
	map->spawn.x = 0;
	map->spawn.y = 0;
	map->map = (t_uchar**)ft_alloc_array(map->h, map->w, sizeof(t_uchar));
	while (i < map->h)
		ft_bzero(map->map[i++], map->w);
	ft_printf("map \"%s\" (%dx%d) created !\n", map->name, map->w, map->h);
	return (0);
}
