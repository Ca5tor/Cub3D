/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 00:00:15 by ltacos            #+#    #+#             */
/*   Updated: 2022/02/09 15:53:35 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return ((void *)0);
	str = (char *)malloc((ft_strlen_mod(s1, 0) + ft_strlen_mod(s2, 0) + 1));
	if (!str)
		return ((void *)0);
	while (s1[i] != '\0')
		str[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	char	a;
	char	*p;

	if (!s)
		return (0);
	a = (char)c;
	p = (char *)s;
	while (*p != a && *p != '\0')
		p++;
	if (*p == a)
		return (p);
	return (NULL);
}

int	ft_strlen_mod(const char *s, int f)
{
	int	len;

	len = 0;
	if (!s)
		return (0);
	if (f == 0)
		while (s[len] != '\0')
			len++;
	else
		while (s[len] != '\n' && s[len] != '\0')
			len++;
	return (len);
}
