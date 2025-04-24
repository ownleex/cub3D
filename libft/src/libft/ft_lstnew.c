/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 00:49:26 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/24 03:43:42 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nouveau;

	nouveau = malloc(sizeof(t_list));
	if (!nouveau)
		return (NULL);
	nouveau->content = content;
	nouveau->next = NULL;
	return (nouveau);
}
