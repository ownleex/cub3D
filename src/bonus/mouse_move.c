/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 02:13:10 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/23 16:44:01 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(int x, int y, t_game *game)
{
	static int last_x = -1;
	int delta_x;
	double sensi;

	sensi = -0.003;
	(void)y;
	if (last_x != -1)
	{
		delta_x = x - last_x;
		if (delta_x != 0)
			rotate(game, -delta_x * sensi);
	}
	last_x = x;
	return (0);
}