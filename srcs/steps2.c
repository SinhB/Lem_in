/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:20:06 by mjouffro          #+#    #+#             */
/*   Updated: 2019/09/23 19:30:15 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			len_max2(t_lemin *lemin, t_allpaths *head, int index)
{
	unsigned int	len_max;
	unsigned int	cnt;
	t_allpaths		*tmp;
	int i = 0;

	cnt = 0;
	tmp = head;
	len_max = tmp->len;
	while (i < index)
	{	
		len_max = len_max < tmp->len ? tmp->len : len_max;
		cnt++;
		tmp = tmp->next;
		i++;
	}
	lemin->nb_paths = cnt;
	return (len_max);
}

unsigned int			get_total2(t_lemin *lemin, t_allpaths *head, int index)
{
	unsigned int	total;
	unsigned int	max_steps;
	unsigned int	prev_max_len;
	t_allpaths		*tmp;
	int i = 0;

	tmp = head;
	prev_max_len = len_max2(lemin, tmp, index);
	total = 0;
	max_steps = lemin->max_steps1;
	while (i < index)
	{
		tmp->max_steps = ((prev_max_len + 1) - tmp->len);
		total += tmp->max_steps;
		tmp = tmp->next;
		i++;
	}
	return (total);
}

unsigned int			nbr_steps2(t_lemin *lemin, t_allpaths *head, int index)
{
	unsigned int	max_steps;
	unsigned int	max = 0;
	unsigned int	reste;
	int i = 0;
	t_allpaths		*tmp;

	max_steps = lemin->max_steps1;
	tmp = head;
	tmp->total = get_total2(lemin, tmp, index);
	if (tmp->total > lemin->nb_ants)
		return (0);
	lemin->remainder = (lemin->nb_ants - tmp->total) / lemin->nb_paths;
	reste = lemin->nb_ants - (lemin->remainder * lemin->nb_paths + tmp->total);
	while (i < index)
	{
		tmp->max_steps += (lemin->remainder + tmp->len + (reste ? 1 : 0) - 1);
		if (max < tmp->max_steps)
			max = tmp->max_steps;
		tmp = tmp->next;
		i++;
		if (reste > 0)
			reste--;
	}
//	tmp = head;
	max_steps = max;
	if (max_steps > lemin->max_steps1)
		return (0);
	else
		return (max_steps);
}

int			max_stepsek(t_lemin *lemin, t_allpaths *head)
{
	int			nb_paths;
	int			tmp = 1;
	int			max = lemin->nb_paths;

	nb_paths = 1;
	lemin->max_steps1 = INT_MAX;
	while (nb_paths < (max + 1))
	{
		if ((tmp = nbr_steps2(lemin, head, nb_paths)) == 0)
			return (0);
		else
			lemin->max_steps1 = tmp;
		nb_paths++;
		lemin->path_max_len = head->len;
		ft_printf("{yellow}---max len is %d{reset}\n", head->len);
		ft_printf("{red} nb paths is : %d\n{reset}", nb_paths);
	}
	return (1);
}