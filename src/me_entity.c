/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_entity.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 14:50:53 by pribault          #+#    #+#             */
/*   Updated: 2017/06/12 17:47:00 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_editor.h"

double	ft_atod(char *s)
{
	t_uchar	pow;
	double	n;
	char	neg;
	int		i;

	neg = 1;
	n = 0;
	i = 0;
	while (s[i] == ' ' || (s[i] > 8 && s[i] < 14) || s[i] == 0)
		i++;
	if (s[i] == '+' || s[i] == '-')
		neg = 44 - s[i++];
	while (s[i] <= '9' && s[i] >= '0')
		n = n * 10 + s[i++] - 48;
	if (s[i++] == '.')
	{
		pow = 1;
		while (s[i] <= '9' && s[i] >= '0')
		{
			n += ((double)(s[i++] - '0') / ft_power(10, pow));
			pow++;
		}
	}
	return (n * neg);
}

char	map_remove_entity(t_map *map, char **instruct)
{
	t_list	*prev;
	t_list	*list;
	int		id;
	int		i;

	if (!map->magic)
		return (ft_error(4));
	list = map->entities;
	id = ft_atoi(instruct[1]);
	i = 0;
	while (list && i < id)
	{
		prev = list;
		list = list->next;
		i++;
	}
	if (!list || i != id)
		return (1);
	if (list == map->entities)
		map->entities = list->next;
	else
		prev->next = list->next;
	free(list->content);
	free(list);
	return (0);
}

char	map_add_entity(t_map *map, char **instruct)
{
	t_entity	entity;

	if (!map->magic)
		return (ft_error(4));
	entity.pos.x = ft_atod(instruct[1]) - 1;
	entity.pos.y = ft_atod(instruct[2]) - 1;
	entity.angle = (ft_atoi(instruct[3]) * 2 * PI) / 360;
	entity.id = ft_atoi(instruct[4]);
	ft_lstadd(&map->entities, ft_lstnew(&entity, sizeof(t_entity)));
	return (0);
}
