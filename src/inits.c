/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 00:44:23 by ltacos            #+#    #+#             */
/*   Updated: 2022/08/26 04:51:10 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	get_size_map(char **map)
{
	int	i;
	int	j;
	int	size;

	size = 0;
	i = -1;
	while (++i < 8)
	{
		j = -1;
		while (++j < 8)
		{
			if (map[i][j] == '1')
			{
				printf("ch=%c\n", map[i][j]);
				size += 1;
			}
				
		}
	}
	return (size);
}

int	cheak_char(char c)
{
	static const char	type_block[7] = {' ', '0', '1', 'N', 'S', 'E', 'W'};
	int					i;
	int					type;

	i = -1;
	type = 0;
	while (++i != 7 && type != 1)
		type = (c == type_block[i]);
	type = (int)type_block[type * i - 1];
	if (type == -1)
		type = (int)type_block[0];
	return (type);
}



t_2D_map	*init_2d_map(char **map)
{
	t_2D_map	*mini_map;
	t_obj		*new_obj;
	int			i;
	int			j;

	mini_map = (t_2D_map *)malloc(sizeof(t_2D_map));
	if (!mini_map)
		return (NULL);
	mini_map->size_obj = 50;
	new_obj = (t_obj *)malloc(sizeof(t_obj) * get_size_map(map));
	printf("SIZE=%d\n", get_size_map(map));
	if (!new_obj)
		return (free(mini_map), NULL);
	i = -1;
	int count = 0;
	while (++i < 8)
	{
		int j = -1;
		while (++j < 8)
		{
			if(map[i][j] == '1')
			{
				new_obj[count].x = j;
				new_obj[count].y = i;
				new_obj[count].type = cheak_char(map[i][j]);
				new_obj[count].colr = 0;
				count++;
			}
		}
	}
	printf("123count=%d\n", count);
	mini_map->obj = new_obj;
	return (mini_map);
}
