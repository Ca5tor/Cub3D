/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:13:17 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/26 20:16:16 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
/* ------------------ GET_RGB ------------------*/

int	pars_is_char_number(char *str)
{
	int	i;
	int	number;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	number = ft_atoi(str);
	if (number < 0 || number > 255)
		return (-1);
	return (number);
}

int	*pars_get_rgb(char *str)
{
	int		i;
	int		flag;
	int		*rgb;
	char	**str_arr;

	rgb = malloc(sizeof(int) * 3);
	flag = 1;
	str_arr = ft_split(str, ',');
	if (pars_char_arr_length(str_arr) != 3)
		flag = 0;
	i = -1;
	while (flag && str_arr[++i])
	{
		rgb[i] = pars_is_char_number(str_arr[i]);
		if (ft_strlen(str_arr[i]) > 3 || rgb[i] == -1)
			flag = 0;
	}
	pars_free_char_arr(str_arr);
	if (flag == 0)
	{
		free(rgb);
		return (NULL);
	}
	return (rgb);
}

/* ------------------ UTILS ------------------*/

char	*last_strstr(char *haystack, char *needle)
{
	char	*p;
	char	*result;

	if (*needle == '\0')
		return ((char *) haystack);
	result = NULL;
	while (1)
	{
		p = ft_strstr(haystack, needle);
		if (p == NULL)
			break ;
		result = p;
		haystack = p + 1;
	}
	return (result);
}

char	**add_str(char **arr, char *str)
{
	int		i;
	int		len;
	char	**new_arr;

	len = 0;
	if (arr)
		while (arr[len])
			len++;
	new_arr = malloc(sizeof(char *) * (len + 2));
	if (!new_arr)
		return (NULL);
	new_arr[len + 1] = NULL;
	new_arr[len] = str;
	i = 0;
	while (arr && arr[i] != NULL)
	{
		new_arr[i] = arr[i];
		i++;
	}
	free(arr);
	return (new_arr);
}

char	**ft_split2(char *str, char token)
{
	int		i;
	char	**arr;

	arr = malloc(sizeof(char *) * 3);
	if (!arr)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != token)
		i++;
	arr[0] = ft_substr(&str[0], 0, i);
	while (str[i] == token)
		i++;
	arr[1] = ft_substr(&str[0], i, ft_strlen(&str[i]));
	arr[2] = NULL;
	return (arr);
}
