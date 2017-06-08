/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_editor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 10:27:02 by pribault          #+#    #+#             */
/*   Updated: 2017/05/29 15:27:26 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_editor.h"

t_instruct	g_instruct[] =
{
	{"create", &map_create, 3},
	{"push", &map_push, 0},
	{"rm", &map_rm, 1},
	{"dump", &map_dump, 0},
	{"load", &map_load, 1},
	{"unload", &map_unload, 0},
	{"set_spawn", &map_set_spawn, 2},
	{"set_block", &map_set_block, 3},
	{"draw_line", &map_set_line, 5},
	{"add_entity", &map_add_entity, 4},
	{"remove_entity", &map_remove_entity, 1},
	{"help", &map_help, 0},
	{"exit", &map_exit, 0},
	{NULL, NULL, 0}
};

void	execute_instruction(t_map *map, char **instruct)
{
	t_uchar	i;

	i = 0;
	while (g_instruct[i].name)
	{
		if (!ft_strcmp(instruct[0], g_instruct[i].name))
		{
			if (ft_arraylen(instruct) == g_instruct[i].args + 1)
				g_instruct[i].fct(map, instruct);
			else
				ft_printf("error: %s need %d arguments\n", instruct[0],
				g_instruct[i].args);
			return ;
		}
		i++;
	}
	ft_printf("instruction %s not recognized\n", instruct[0]);
}

int		main(void)
{
	t_map	map;
	char	**instruct;
	char	*line;

	ft_bzero(&map, sizeof(t_map));
	ft_putstr("$> ");
	while (ft_get_next_line(0, &line))
	{
		instruct = ft_strsplit(line, ' ');
		execute_instruction(&map, instruct);
		ft_free_array((void**)instruct, ft_arraylen(instruct) + 1);
		free(line);
		ft_putstr("$> ");
	}
	map_exit(&map, NULL);
	return (0);
}
