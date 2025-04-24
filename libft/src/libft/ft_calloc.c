/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:07:22 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/24 03:41:44 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*memory;

	memory = (void *)malloc(size * count);
	if (memory == NULL)
		return (NULL);
	ft_bzero(memory, size * count);
	return (memory);
}
