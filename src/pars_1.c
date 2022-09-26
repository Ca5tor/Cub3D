/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:13:38 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/26 20:16:11 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	pars_ends_with(char *str, char *end)
{
	int		strlen;
	int		endlen;
	char	*occur;

	strlen = ft_strlen(str);
	endlen = ft_strlen(end);
	occur = last_strstr(str, end);
	if (strlen >= endlen && occur == str + (strlen - endlen))
		return (1);
	return (0);
}

int	pars_starts_with(char *str, char *pre)
{
	return (ft_strncmp(pre, str, ft_strlen(pre)) == 0);
}

int	pars_char_arr_length(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

void	pars_free_char_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/* ------------------ ARGC CHECK ------------------*/

void	pars_arg_check(int argc, char **argv)
{
	if (argc != 2)
		pars_exit_with_error(BAD_ARGUMENT);
	if (!pars_ends_with(argv[1], ".cub"))
		pars_exit_with_error(BAD_EXTENSION);
}
