/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_blocks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 16:54:38 by pribault          #+#    #+#             */
/*   Updated: 2017/06/12 19:03:48 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	fill_array(t_env *env, char *line, int fd, t_uchar n)
{
	char	**params;

	n = 0;
	while (ft_get_next_line(fd, &line) > 0)
	{
		params = ft_strsplit(line, '\t');
		if (ft_arraylen(params) != 7)
			exit(1);
		env->blocks[n].name = ft_strdup(params[0]);
		env->blocks[n].h = ft_atoi(params[1]);
		env->blocks[n].color = smlx_create_color(ft_atoi(params[2]),
		ft_atoi(params[3]), ft_atoi(params[4]), ft_atoi(params[5]));
		if (ft_strcmp("NULL", params[6]))
			env->blocks[n].texture = smlx_new_image_xpm(&env->win, params[6]);
		else
			env->blocks[n].texture = NULL;
		ft_free_array((void**)params, 8);
		free(line);
		n++;
	}
	env->blocks[n].name = NULL;
	free(line);
}

void	free_blocks(t_env *env)
{
	t_uchar	n;

	n = 0;
	while (env->blocks[n].name)
	{
		free(env->blocks[n].name);
		if (env->blocks[n].texture)
			smlx_destroy_image(&env->win, &env->blocks[n].texture);
		n++;
	}
	free(env->blocks);
}

void	load_blocks(t_env *env)
{
	t_uchar	n;
	char	*line;
	int		fd;

	n = 0;
	if ((fd = open("blocks.blocks", O_RDONLY)) < 0)
		return ;
	while (ft_get_next_line(fd, &line) > 0)
	{
		n++;
		free(line);
	}
	free(line);
	env->blocks = (t_block*)malloc(sizeof(t_block) * (n + 1));
	ft_bzero(env->blocks, sizeof(t_block) * (n + 1));
	lseek(fd, 0, SEEK_SET);
	fill_array(env, line, fd, n);
	close(fd);
}
