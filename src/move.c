/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 15:38:35 by pribault          #+#    #+#             */
/*   Updated: 2017/06/12 13:31:44 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	move_player(t_env *env, double x, double y)
{
	t_point	block;
	t_point	pos;

	block.x = convert(env->cam.x + x);
	block.y = convert(env->cam.y + y);
	pos.x = convert(env->cam.x);
	pos.y = convert(env->cam.y);
	if (block.x < 0 || block.x >= env->map.w || block.y < 0 ||
	block.y >= env->map.h)
	{
		env->cam.x += x;
		env->cam.y += y;
	}
	else
	{
		if (pos.x < 0 || pos.x >= env->map.w || !env->map.map[block.y][pos.x])
			env->cam.y += y;
		if (pos.y < 0 || pos.y >= env->map.h || !env->map.map[pos.y][block.x])
			env->cam.x += x;
	}
}
