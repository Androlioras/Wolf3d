/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 10:27:02 by pribault          #+#    #+#             */
/*   Updated: 2017/05/29 15:30:52 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_editor.h"

char	map_exit(t_map *map, char **instruct)
{
	char	*line;

	if (map && map->magic)
	{
		ft_printf("save map before exit ? (y/n)\n");
		ft_get_next_line(0, &line);
		if (!ft_strcmp("y", line))
			map_push(map, instruct);
		map_unload(map, instruct);
	}
	ft_putendl("don't kill me noooooooo x___x");
	exit(0);
	return (0);
}
