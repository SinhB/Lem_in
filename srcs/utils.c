/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:45:00 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:10 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		add_line_to_str(t_lemin *lemin, char *str)
{
	char	*tmp;

	str = ft_strjoin(str, "\n");
	tmp = lemin->map;
	if (lemin->map == NULL)
		lemin->map = ft_strdup(str);
	else
		lemin->map = ft_strjoin(tmp, str);
	free(tmp);
	ft_strdel(&str);
}

void		addlinks(t_links **links, t_links *new)
{
	new->next = (*links);
	*links = new;
}
