/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   me_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 10:27:02 by pribault          #+#    #+#             */
/*   Updated: 2017/06/12 11:53:23 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_editor.h"

char	map_help(t_map *map, char **instruct)
{
	map++;
	instruct++;
	ft_putendl("___ list of commands for map_editor ___\n");
	ft_putendl("  create    <name> <width> <height>");
	ft_putendl("  rm        <name>");
	ft_putendl("  load      <name>");
	ft_putendl("  unload");
	ft_putendl("  push");
	ft_putendl("  set_spawn     <x> <y>");
	ft_putendl("  set_block     <x> <y> <block>");
	ft_putendl("  draw_line     <a.x> <a.y> <b.x> <b.y> <block>");
	ft_putendl("  add_entity    <x> <y> <angle in degrees> <entity>");
	ft_putendl("  remove_entity <id>");
	ft_putendl("  dump");
	ft_putendl("  exit");
	return (0);
}
