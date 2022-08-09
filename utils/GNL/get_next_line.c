/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 00:00:06 by ltacos            #+#    #+#             */
/*   Updated: 2022/02/09 15:53:29 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_get_line(char *rem)
{
	char	*line;
	int		i;

	i = 0;
	if (!rem[i])
		return (NULL);
	line = (char *)malloc(ft_strlen_mod(rem, 1) + 2);
	if (!line)
		return (NULL);
	while (rem[i] != '\n' && rem[i] != '\0')
	{
		line[i] = rem[i];
		i++;
	}
	if (rem[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*ft_read(int fd, char *rem)
{
	char	*buf;
	int		byte_read;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	byte_read = 1;
	while (byte_read != 0 && !ft_strchr(rem, '\n'))
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free (buf);
			return (NULL);
		}
		buf[byte_read] = '\0';
		rem = ft_strjoin(rem, buf);
	}
	free (buf);
	return (rem);
}

static char	*ft_get_rem(char *rem)
{
	char	*real_rem;
	int		i;
	int		j;

	i = ft_strlen_mod(rem, 1);
	if (!rem[i])
	{
		free(rem);
		return (NULL);
	}
	real_rem = (char *)malloc(ft_strlen_mod(rem, 0) - i + 1);
	if (!real_rem)
		return (NULL);
	i++;
	j = 0;
	while (rem[i])
		real_rem[j++] = rem[i++];
	real_rem[j] = '\0';
	free (rem);
	return (real_rem);
}

char	*get_next_line(int fd)
{
	static char	*rem;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	rem = ft_read(fd, rem);
	if (!rem)
		return (NULL);
	line = ft_get_line(rem);
	rem = ft_get_rem(rem);
	return (line);
}
