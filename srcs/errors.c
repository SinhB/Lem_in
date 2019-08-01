/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabecret <yabecret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 15:32:49 by yabecret          #+#    #+#             */
/*   Updated: 2019/06/05 17:35:05 by yabecret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	rooms_errors(t_lemin *lemin)
{
	if (!(lemin->state & S_ROOMS))
		return (SUCCESS);
	if (lemin->start == NULL || lemin->end == NULL)
		return (SUCCESS);
	return (FAILURE);
}
