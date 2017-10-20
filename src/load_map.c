/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 15:21:11 by pribault          #+#    #+#             */
/*   Updated: 2017/06/12 17:18:45 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	free_map(t_env *env)
{
	t_list	*list;
	t_list	*next;

	ft_free_array((void**)env->map.map, env->map.h);
	list = env->map.entities;
	while (list)
	{
		next = list->next;
		free(list->content);
		free(list);
		list = next;
	}
}

void	fill_map(t_env *env, int fd)
{
	t_entity	entity;
	int			i;

	i = 0;
	env->map.map = (t_uchar**)ft_alloc_array(env->map.h, env->map.w,
	sizeof(t_uchar));
	while (i < env->map.h)
		read(fd, env->map.map[i++], sizeof(t_uchar) * env->map.w);
	while (read(fd, &entity, sizeof(t_entity)) == sizeof(t_entity))
		ft_lstadd(&env->map.entities, ft_lstnew(&entity, sizeof(t_entity)));
}

void	verify_entities(t_env *env)
{
	t_list	*list;
	int		entities;

	entities = 0;
	while (env->entities[entities].name)
		entities++;
	list = env->map.entities;
	while (list)
	{
		if (((t_entity*)list->content)->id >= entities)
			exit(1);
		list = list->next;
	}
}

void	verify_map(t_env *env)
{
	int		blocks;
	int		i[2];

	blocks = 0;
	while (env->blocks[blocks].name)
		blocks++;
	i[0] = 0;
	while (i[0] < env->map.h)
	{
		i[1] = 0;
		while (i[1] < env->map.w)
			if (env->map.map[i[0]][i[1]++] >= blocks)
				exit(1);
		i[0]++;
	}
	verify_entities(env);
}

void	load_map(t_env *env, char *name)
{
	static char	*map;
	t_point		spawn;
	t_uint		magic;
	char		*file;
	int			fd;

	env->map.entities = NULL;
	if (name)
		map = name;
	file = ft_joinf("%s.w3d", map);
	if ((fd = open(file, O_RDONLY)) < 0)
		exit(1);
	free(file);
	if ((read(fd, &magic, sizeof(t_uint))) == sizeof(t_uint) &&
	magic == MAGIC && (read(fd, &env->map.w, sizeof(int))) == sizeof(int) &&
	(read(fd, &env->map.h, sizeof(int))) == sizeof(int) && (read(fd, &spawn,
	sizeof(t_point))) == sizeof(t_point))
		fill_map(env, fd);
	else
		ft_exit(env, 1);
	env->cam.x = spawn.x - 1;
	env->cam.y = spawn.y - 1;
	close(fd);
	verify_map(env);
}
