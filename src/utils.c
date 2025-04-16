/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:34:43 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/16 18:48:57 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_ext(char *file, char *ext)
{
	int	file_len;
	int	ext_len;

	if (!file || !ext)
		return (false);
	file_len = ft_strlen(file);
	ext_len = ft_strlen(ext);
	
	if (file_len <= ext_len)
		return (false);
	return (ft_strncmp(file + file_len - ext_len, ext, ext_len + 1) == 0);
}

int	create_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	sign(double x)
{
	if (x < 0)
		return (-1);
	return (1);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}