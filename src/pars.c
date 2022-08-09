/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 21:05:16 by ltacos            #+#    #+#             */
/*   Updated: 2022/07/18 21:16:29 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	pars(t_cub *cub, char **strs)
{
	while (*strs)
	{
		if (ft_strncmp(*strs, "NO", 2))
			cub->idntfrs[0] = ft_strdup(*strs + 2);
		if (ft_strncmp(*strs, "SO", 2))
			cub->idntfrs[1] = ft_strdup(*strs + 2);
		if (ft_strncmp(*strs, "WE", 2))
			cub->idntfrs[2] = ft_strdup(*strs + 2);
		if (ft_strncmp(*strs, "EA", 2))
			cub->idntfrs[3] = ft_strdup(*strs + 2);
		if (ft_strncmp(*strs, "F", 1))
			cub->idntfrs[4] = ft_strdup(*strs + 1);
		if (ft_strncmp(*strs, "C", 1))
			cub->idntfrs[5] = ft_strdup(*strs + 1);
		strs++;
	}
}

