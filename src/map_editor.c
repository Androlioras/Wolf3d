/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_editor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 10:27:02 by pribault          #+#    #+#             */
/*   Updated: 2017/06/12 14:05:25 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_editor.h"

t_instruct	*get_instructs(void)
{
	static t_instruct	instructs[] = {
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

	return (instructs);
}

void		execute_instruction(t_map *map, char **instruct,
			t_instruct *instructs)
{
	t_uchar		i;

	i = 0;
	instructs = get_instructs();
	if (!instruct || !instruct[0])
		return ;
	while (instructs[i].name)
	{
		if (!ft_strcmp(instruct[0], instructs[i].name))
		{
			if (ft_arraylen(instruct) == instructs[i].args + 1)
				instructs[i].fct(map, instruct);
			else
				ft_printf("error: %s need %d arguments\n", instruct[0],
				instructs[i].args);
			return ;
		}
		i++;
	}
	ft_printf("instruction %s not recognized\n", instruct[0]);
}

int			main(void)
{
	t_instruct	*instructs;
	t_map		map;
	char		**instruct;
	char		*line;

	ft_bzero(&map, sizeof(t_map));
	instructs = get_instructs();
	ft_putstr("$> ");
	while (ft_get_next_line(0, &line))
	{
		instruct = ft_strsplit(line, ' ');
		execute_instruction(&map, instruct, instructs);
		ft_free_array((void**)instruct, ft_arraylen(instruct) + 1);
		free(line);
		ft_putstr("$> ");
	}
	map_exit(&map, NULL);
	return (0);
}
