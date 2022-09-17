/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 01:27:11 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/17 03:31:29 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

double	find_max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	find_min(double x, double y)
{
	if (x < y)
		return (x);
	return (y);
}

double	mod(double a)
{
	if (a < 0)
		return (-a);
	return (a);
}

int	cheack_pos(t_pos a, t_pos *b)
{
	double	cx;
	double	cy;
	int		i;

	i = -1;
	while (++i < 31)
	{
		cx = b[i].x + BLOCK_SIZE;
		cy = b[i].y + BLOCK_SIZE;
		if (a.x > b[i].x && a.y > b[i].y && a.x < cx && a.y < cy)
			return (1);
	}
	return (0);
}

int	chek_key(int key)
{
	return (key == TURN_L || key == TURN_R \
		|| key == M_DIRECTLY || key == M_BACK \
		|| key == M_RIGHT || key == M_LEFT \
		|| key == EXIT_WINDW);
}
