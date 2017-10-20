/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 14:30:25 by pribault          #+#    #+#             */
/*   Updated: 2017/06/12 16:45:22 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		red_cross(t_env *env)
{
	free_map(env);
	free_blocks(env);
	free_entities(env);
	smlx_destroy_image(&env->win, &env->img);
	smlx_destroy_image(&env->win, &env->img2);
	smlx_destroy_image(&env->win, &env->back);
	smlx_destroy_image(&env->win, &env->sky);
	smlx_destroy_window(&env->win);
	exit(0);
	return (0);
}

void	wolf_keys2(t_env *env)
{
	if (env->win.keys.tab[15])
	{
		free_blocks(env);
		load_blocks(env);
		free_entities(env);
		load_entities(env);
		free_map(env);
		load_map(env, NULL);
		ft_printf("blocks and map reloaded !\n\n");
	}
}

void	wolf_keys(t_env *env)
{
	if (env->win.keys.tab[123])
		env->cam.angle -= 0.03;
	if (env->win.keys.tab[124])
		env->cam.angle += 0.03;
	if (env->win.keys.tab[126])
		move_player(env, cos(env->cam.angle) * PLAYER_SPEED,
		sin(env->cam.angle) * PLAYER_SPEED);
	if (env->win.keys.tab[125])
		move_player(env, -cos(env->cam.angle) * PLAYER_SPEED,
		-sin(env->cam.angle) * PLAYER_SPEED);
	wolf_keys2(env);
	env->cam.angle += (env->cam.angle < -PI) ? 2 * PI : 0;
	env->cam.angle += (env->cam.angle > PI) ? -2 * PI : 0;
}

void	ft_keys(t_env *env)
{
	if (env->win.keys.tab[53])
		ft_exit(env, 0);
	wolf_keys(env);
}
