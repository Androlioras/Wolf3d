/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smlx_get_fps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 00:21:47 by pribault          #+#    #+#             */
/*   Updated: 2017/05/19 00:52:09 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsmlx.h"
#include <sys/time.h>

t_uint	smlx_get_fps(void)
{
	static struct timeval	prev;
	static struct timeval	t;
	t_uint					fps;

	gettimeofday(&t, NULL);
	fps = ((t.tv_sec * 1000000 + t.tv_usec) - (prev.tv_sec * 1000000 +
	prev.tv_usec));
	prev = t;
	return (1000000 / fps);
}
