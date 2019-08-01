/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabecret <yabecret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:28:08 by yabecret          #+#    #+#             */
/*   Updated: 2019/06/26 17:29:31 by yabecret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_start(t_lemin *lemin)
{
	if (lemin->state & S_START)
	{
		lemin->state &= ~S_START;
		return (1);
	}
	return (0);
}

int		is_end(t_lemin *lemin)
{
	if (lemin->state & S_END)
	{
		lemin->state &= ~S_END;
		return (1);
	}
	return (0);
}
