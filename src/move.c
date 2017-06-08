/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 15:38:35 by pribault          #+#    #+#             */
/*   Updated: 2017/05/29 15:51:57 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	move_player(t_env *env, double x, double y)
{
	t_point	block;

	block.x = convert(env->cam.x + x);
	block.y = convert(env->cam.y + y);
	if (block.x < 0 || block.x >= env->map.w || block.y < 0 ||
	block.y >= env->map.h)
	{
		env->cam.x += x;
		env->cam.y += y;
	}
	else
	{
		if (!env->map.map[block.y][convert(env->cam.x)])
			env->cam.y += y;
		if (!env->map.map[convert(env->cam.y)][block.x])
			env->cam.x += x;
	}
}
