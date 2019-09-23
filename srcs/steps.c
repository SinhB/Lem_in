/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:19:27 by mjouffro          #+#    #+#             */
/*   Updated: 2019/09/23 19:32:25 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			len_max(t_lemin *lemin, t_allpaths *head)
{
	unsigned int	len_max;
	unsigned int	cnt;
	t_allpaths		*tmp;

	cnt = 0;
	tmp = head;
	len_max = tmp->len;
	while (tmp)
	{
		len_max = len_max < tmp->len ? tmp->len : len_max;
		tmp = tmp->next;
		cnt++;
	}
	lemin->nb_paths = cnt;
	return (len_max);
}

unsigned int			get_total(t_lemin *lemin, t_allpaths *head, int final)
{
	unsigned int	total;
	unsigned int	max_steps;
	unsigned int	max_len;
	t_allpaths		*tmp;

	tmp = head;
	max_len = len_max(lemin, tmp);
	total = 0;
	max_steps = lemin->max_steps;
	while (tmp && (final < (lemin->nb_paths + 1)))
	{
		tmp->max_steps = ((max_len + 1) - tmp->len);
		total += tmp->max_steps;		
		tmp = tmp->next;
	}
	return (total);
}

unsigned int			nbr_steps(t_lemin *lemin, t_allpaths *head, int final)
{
	unsigned int	max_steps;
	unsigned int	max = 0;
	unsigned int	total;
	unsigned int	reste;
	t_allpaths		*tmp;

	max_steps = lemin->max_steps;
	tmp = head;
	
	total = get_total(lemin, tmp, final);
	if (tmp->total > lemin->nb_ants)
		return (0);
	lemin->remainder = (lemin->nb_ants - tmp->total) / lemin->nb_paths;
	reste = lemin->nb_ants - (lemin->remainder * lemin->nb_paths + total);
	
	while (tmp)
	{
		tmp->max_steps += (lemin->remainder + tmp->len + (reste ? 1 : 0) - 1);
		if (max < tmp->max_steps)
			max = tmp->max_steps;
		lemin->path_max_len = tmp->len;
		tmp = tmp->next;
		if (reste > 0)
			reste--;
	}
	max_steps = max;
	if (max_steps > lemin->max_steps)
		return (0);
	else
		return (max_steps);
}