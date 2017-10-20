/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_unload.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 10:27:02 by pribault          #+#    #+#             */
/*   Updated: 2017/06/12 11:52:13 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_editor.h"

char	map_unload(t_map *map, char **instruct)
{
	t_list	*list;
	t_list	*next;

	if (!map->magic)
		return (ft_error(4));
	instruct++;
	if (map->name)
		free(map->name);
	if (map->map)
		ft_free_array((void**)map->map, map->h);
	list = map->entities;
	while (list)
	{
		next = list->next;
		free(list->content);
		free(list);
		list = next;
	}
	ft_bzero(map, sizeof(t_map));
	return (0);
}
