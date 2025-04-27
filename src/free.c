/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:17:44 by cparodi           #+#    #+#             */
/*   Updated: 2025/04/27 16:17:46 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_file(t_game *game)
{
	int	i;

	if (!game->file)
		return ;
	i = 0;
	while (game->file[i])
	{
		free(game->file[i]);
		i++;
	}
	free(game->file);
	game->file = NULL;
}
