/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_entities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 14:19:32 by pribault          #+#    #+#             */
/*   Updated: 2017/06/12 19:03:56 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	fill_array_2(t_env *env, char *line, int fd, t_uchar n)
{
	char	**params;

	n = 0;
	while (ft_get_next_line(fd, &line) > 0)
	{
		params = ft_strsplit(line, '\t');
		if (ft_arraylen(params) != 8)
			exit(1);
		env->entities[n].name = ft_strdup(params[0]);
		env->entities[n].h = ft_atoi(params[1]);
		env->entities[n].y = ft_atoi(params[2]);
		env->entities[n].color = smlx_create_color(ft_atoi(params[3]),
		ft_atoi(params[4]), ft_atoi(params[5]), ft_atoi(params[6]));
		if (ft_strcmp("NULL", params[7]))
			env->entities[n].texture = smlx_new_image_xpm(&env->win, params[7]);
		else
			env->entities[n].texture = NULL;
		ft_free_array((void**)params, 8);
		free(line);
		n++;
	}
	env->entities[n].name = NULL;
	free(line);
}

void	free_entities(t_env *env)
{
	t_uchar	n;

	n = 0;
	while (env->entities[n].name)
	{
		free(env->entities[n].name);
		if (env->entities[n].texture)
			smlx_destroy_image(&env->win, &env->entities[n].texture);
		n++;
	}
	free(env->entities);
}

void	load_entities(t_env *env)
{
	t_uchar	n;
	char	*line;
	int		fd;

	n = 0;
	if ((fd = open("entities.ett", O_RDONLY)) < 0)
		return ;
	while (ft_get_next_line(fd, &line) > 0)
	{
		n++;
		free(line);
	}
	free(line);
	env->entities = (t_ent*)malloc(sizeof(t_ent) * (n + 1));
	ft_bzero(env->entities, sizeof(t_ent) * (n + 1));
	lseek(fd, 0, SEEK_SET);
	fill_array_2(env, line, fd, n);
	close(fd);
}
