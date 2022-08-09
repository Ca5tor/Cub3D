/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:31:20 by ltacos            #+#    #+#             */
/*   Updated: 2022/08/04 11:33:02 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#define MSG_ARG "Error: Used ./cub3d file.cub\n"
#define MSG_FILE "Error: File is empty\n"

void	exit_err(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(1);
}

void	_check_arg(int arg, char *s)
{
	int	len;

	if (arg != 2)
		exit_err (MSG_ARG);
	len = ft_strlen(s) - 4;
	if (len == 0 || !ft_strnstr(&s[len], ".cub", 4))
		exit_err (MSG_ARG);
}

int	main(int ac, char **av)
{
	t_data	*data;

	_check_arg(ac, av[1]);
	data = init_data();
	data->file_lines = reader_file(av[1]);
	int i = -1;
	while (data->file_lines[++i])
	{
		printf("Str:%s\n", data->file_lines[i]);
	}
	return (0);
}
