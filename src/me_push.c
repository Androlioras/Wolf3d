/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 10:27:02 by pribault          #+#    #+#             */
/*   Updated: 2017/05/29 14:59:31 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_editor.h"

void	push_entities(t_map *map, int fd)
{
	t_list	*list;

	list = map->entities;
	while (list)
	{
		write(fd, list->content, sizeof(t_entity));
		list = list->next;
	}
}

char	map_push(t_map *map, char **instruct)
{
	char	*file;
	int		fd;
	int		i;

	instruct++;
	if (!map->magic)
		return (ft_error(3));
	i = 0;
	file = ft_joinf("%s.w3d", map->name);
	if ((fd = open(file, O_TRUNC | O_CREAT | O_WRONLY, S_IRWXU)) < 0)
	{
		free(file);
		return (ft_printf("can't open file\n"));
	}
	write(fd, &map->magic, sizeof(t_uint));
	write(fd, &map->w, sizeof(int));
	write(fd, &map->h, sizeof(int));
	write(fd, &map->spawn, sizeof(t_point));
	while (i < map->h)
		write(fd, map->map[i++], sizeof(t_uchar) * map->w);
	push_entities(map, fd);
	close(fd);
	ft_printf("map pushed in %s\n", file);
	free(file);
	return (0);
}
