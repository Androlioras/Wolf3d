/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 16:19:07 by pribault          #+#    #+#             */
/*   Updated: 2017/05/23 14:56:47 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_block	g_blocks[] =
{
	{"air", 0, {0, 0, 255, 255}, NULL, NULL},
	{"stone", 500, {64, 64, 64, 0}, "textures/stone.xpm", NULL},
	{"glass", 500, {255, 255, 0, 0}, "textures/glass.xpm", NULL},
	{"wood", 500, {0, 255, 255, 0}, "textures/wood.xpm", NULL},
	{NULL, 0, {0, 0, 0, 255}, NULL, NULL}
};
