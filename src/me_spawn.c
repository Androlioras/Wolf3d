/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_spawn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 10:27:02 by pribault          #+#    #+#             */
/*   Updated: 2017/05/29 11:07:13 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_editor.h"

char	map_set_spawn(t_map *map, char **instruct)
{
	map->spawn.x = ft_atoi(instruct[1]);
	map->spawn.y = ft_atoi(instruct[2]);
	return (0);
}
