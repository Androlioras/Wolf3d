/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 10:27:02 by pribault          #+#    #+#             */
/*   Updated: 2017/05/29 14:47:08 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_editor.h"

void	read_file(t_map *map, int fd)
{
	t_entity	entity;
	int			i;

	i = 0;
	map->map = (t_uchar**)ft_alloc_array(map->h, map->w, sizeof(t_uchar));
	while (i < map->h)
		read(fd, map->map[i++], sizeof(t_uchar) * map->w);
	while (read(fd, &entity, sizeof(t_entity)) == sizeof(t_entity))
		ft_lstadd(&map->entities, ft_lstnew(&entity, sizeof(t_entity)));
}

char	map_load(t_map *map, char **instruct)
{
	char	*file;
	int		fd;

	if (map->magic)
		map_exit(map, NULL);
	file = ft_joinf("%s.w3d", instruct[1]);
	if ((fd = open(file, O_RDONLY)) < 0)
	{
		free(file);
		return (ft_printf("can't find %s\n", file));
	}
	free(file);
	if ((read(fd, &map->magic, sizeof(t_uint))) == sizeof(t_uint) &&
	map->magic == MAGIC && (read(fd, &map->w, sizeof(int))) == sizeof(int) &&
	(read(fd, &map->h, sizeof(int))) == sizeof(int) && (read(fd, &map->spawn,
	sizeof(t_point))) == sizeof(t_point))
		read_file(map, fd);
	else
	{
		map->magic = 0;
		ft_printf("error, file is not well formated\n");
	}
	map->name = ft_strdup(instruct[1]);
	close(fd);
	return (0);
}
