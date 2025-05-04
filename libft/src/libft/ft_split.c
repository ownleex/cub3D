/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:17:41 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/05/04 21:21:12 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	ft_count_words(const char *s, char c)
{
	int	count;
	int	i;

	if (!s || !*s)
		return (0);
	count = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

static void	ft_free(char **s2, int i)
{
	while (i--)
		free(s2[i]);
	free(s2);
}

static char	**ft_split_words(const char *s, char c, char **s2, int count)
{
	int	i;
	int	start;
	int	word;

	i = 0;
	start = 0;
	word = 0;
	while (word < count)
	{
		start = i;
		while (s[i] && s[i] != c)
			i++;
		s2[word] = ft_substr(s, start, i - start);
		if (!s2[word++])
		{
			ft_free(s2, word - 1);
			return (NULL);
		}
		if (s[i] == c)
			i++;
	}
	s2[word] = NULL;
	return (s2);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	int		count;

	if (!s)
		return (NULL);
	count = ft_count_words(s, c);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	return (ft_split_words(s, c, result, count));
}
