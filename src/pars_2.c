/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:13:42 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/26 20:16:07 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/* ------------------ MAP PARSER ------------------*/

bool	map_is_direction(char c)
{
	return (c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

bool	map_is_allowed_char(char c)
{
	return (c == '0' || c == '1' || map_is_direction(c) || c == ' ');
}

bool	map_is_num_direction(int c)
{
	return (c == NORTH || c == SOUTH
		|| c == EAST || c == WEST);
}

int	**map_get_empty_matrix(int rows, int cols)
{
	int	i;
	int	j;
	int	**matrix;

	i = -1;
	matrix = malloc(rows * sizeof(int *));
	while (++i < rows)
	{
		j = -1;
		matrix[i] = malloc(cols * sizeof(int));
		while (++j < cols)
			matrix[i][j] = SPACE;
	}
	return (matrix);
}

int	**map_copy_matrix(int **matrix, int rows, int cols)
{
	int		i;
	int		j;
	int		**dest;

	i = -1;
	dest = malloc(rows * sizeof(int *));
	while (++i < rows)
	{
		j = -1;
		dest[i] = malloc(cols * sizeof(int));
		while (++j < cols)
			dest[i][j] = matrix[i][j];
	}
	return (dest);
}
