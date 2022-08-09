/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:26:40 by ltacos            #+#    #+#             */
/*   Updated: 2022/02/28 00:03:39 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char const *s, char c)
{
	size_t	word_count;
	size_t	skipper;

	word_count = 0;
	skipper = 1;
	while (*s)
	{
		if (*s != c && skipper)
		{
			skipper = 0;
			word_count++;
		}
		else if (*s++ == c)
			skipper = 1;
	}
	return (word_count);
}

static char const	*skip_equal_chars(char const *s, char c)
{
	while (*s && *s == c)
		s++;
	return (s);
}

static void	create_words(char **words, char const *s, char c, size_t word_count)
{
	char	*pointerator;

	s = skip_equal_chars(s, c);
	while (word_count--)
	{
		pointerator = ft_strchr(s, c);
		if (pointerator != NULL)
		{
			*words = ft_substr(s, 0, pointerator - s);
			s = skip_equal_chars(pointerator, c);
		}
		else
			*words = ft_substr(s, 0, ft_strlen(s) + 1);
		words++;
	}
	*words = NULL;
}

char	**ft_split(char const *s, char c)
{
	size_t	word_count;
	char	**words;

	if (s == NULL)
		return (NULL);
	word_count = count_words(s, c);
	words = malloc(sizeof(char **) * (word_count + 1));
	if (words == NULL)
		return (NULL);
	create_words(words, s, c, word_count);
	return (words);
}
