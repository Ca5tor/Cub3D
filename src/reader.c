/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:10:04 by ltacos            #+#    #+#             */
/*   Updated: 2022/07/20 19:03:52 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#define MSG_FD "Error: File not found\n"
#define MSG_FILE "Error: File is empty\n"

char	**reader_file(char *file)
{
	char	**strs;
	char	*all_str;
	char	*tmp;
	int		fd;

	fd = open(file, O_RDONLY, 0);
	if (fd < 0)
	{
		close(fd);
		exit_err (MSG_FD);
	}
	all_str = get_next_line(fd);
	if (!all_str)
	{
		close(fd);
		exit_err (MSG_FILE);
	}
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		all_str = ft_strjoin(all_str, tmp);
		free(tmp);
	}
	strs = ft_split(all_str, '\n');
	close(fd);
	return (strs);
}

