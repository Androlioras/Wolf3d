/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_spawn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 10:27:02 by pribault          #+#    #+#             */
/*   Updated: 2017/06/12 11:52:06 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_editor.h"

char	map_set_spawn(t_map *map, char **instruct)
{
	if (!map->magic)
		return (ft_error(4));
	map->spawn.x = ft_atoi(instruct[1]);
	map->spawn.y = ft_atoi(instruct[2]);
	return (0);
}
