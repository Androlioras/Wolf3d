/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_rm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 10:27:02 by pribault          #+#    #+#             */
/*   Updated: 2017/05/29 11:06:17 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_editor.h"

char	map_rm(t_map *map, char **instruct)
{
	char	*file;
	char	*line;

	map++;
	ft_printf("are you sure that you want to delete the file %s.w3d ? (y/n)\n",
	instruct[1]);
	ft_get_next_line(0, &line);
	if (!ft_strcmp(line, "n"))
		return (0);
	else if (ft_strcmp(line, "y"))
		return (ft_error(2));
	file = ft_joinf("%s.w3d", instruct[1]);
	remove(file);
	ft_printf("\033[1A\033[K%s deleted\n", file);
	free(file);
	return (0);
}
