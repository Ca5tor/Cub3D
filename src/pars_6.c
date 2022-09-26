/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:13:56 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/26 20:15:55 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	pars_handle_cfg(char **str_arr, t_cub *cub)
{
	int		i;
	int		ret;
	int		flags;
	char	*str;
	char	**key_value;

	i = -1;
	ret = 0;
	flags = 0;
	while (str_arr[++i] && flags != ALL_FLAG && ret == 0)
	{
		if (ft_strlen(str_arr[i]) == 0)
			continue ;
		str = ft_strtrim(str_arr[i], " ");
		key_value = ft_split2(str, ' ');
		ret = pars_handle_str(key_value, &flags, cub);
		pars_free_char_arr(key_value);
		free(str);
	}
	if ((flags != ALL_FLAG || str_arr[i] == NULL) && ret == 0)
		ret = BAD_CONFIG;
	else if (ret == 0 && !map_pre_parse(&str_arr[i], &cub->map))
		ret = BAD_MAP;
	pars_free_char_arr(str_arr);
	return (ret);
}

int	pars_read_cfg(char *file, t_cub *cub)
{
	int		fd;
	char	*line;
	char	**str_arr;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (BAD_FILE);
	str_arr = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		str_arr = add_str(str_arr, ft_strtrim(line, "\n"));
		free(line);
	}
	if (str_arr == NULL)
		return (BAD_CONFIG);
	return (pars_handle_cfg(str_arr, cub));
}
