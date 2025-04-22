/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:35:02 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/20 19:04:00 by ayarmaya         ###   ########.fr       */
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