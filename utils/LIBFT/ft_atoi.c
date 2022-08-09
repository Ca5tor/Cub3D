/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:36:44 by ltacos            #+#    #+#             */
/*   Updated: 2021/11/09 17:23:51 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		flag;
	long	num;

	flag = 1;
	num = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if ((*str == '+' || *str == '-'))
	{
		if (*str == '-')
			flag = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + (*(str++) - 48);
		if (num > 2147483647 && flag == 1)
			return (-1);
		if (num > 2147483648 && flag == -1)
			return (0);
	}
	return (num * flag);
}
