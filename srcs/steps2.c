/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:20:06 by mjouffro          #+#    #+#             */
/*   Updated: 2019/09/24 13:30:29 by mjouffro         ###   ########.fr       */
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
		ft_printf("tmp len is %d\n", tmp->len);
		len_max = len_max < tmp->len ? tmp->len : len_max;
		cnt++;
		tmp = tmp->next;
		i++;
	}
	lemin->nb_paths = cnt;
	ft_printf("cnt is %d\n", cnt);
	return (len_max);
}

unsigned int			get_total2(t_lemin *lemin, t_allpaths *head, int index)
{
	unsigned int	total;
	unsigned int	max_steps;
	unsigned int	max_len;
	t_allpaths		*tmp;
	int i = 0;

	tmp = head;
	max_len = len_max2(lemin, tmp, index);
	ft_printf("max_len is %d\n", max_len);
	total = 0;
	max_steps = lemin->max_steps1;
	while (i < index)
	{
		tmp->max_steps = ((max_len + 1) - tmp->len);
		total += tmp->max_steps;
		tmp = tmp->next;
		i++;
	}
	ft_printf("total is %d\n", total);
	return (total);
}

unsigned int			nbr_steps2(t_lemin *lemin, t_allpaths *head, int index)
{
	unsigned int	max_steps;
	unsigned int	max = 0;
	unsigned int	total;
	unsigned int	remainder;
	unsigned int	reste;
	int i = 0;
	t_allpaths		*tmp;

	max_steps = lemin->max_steps1;
	tmp = head;
	total = get_total2(lemin, tmp, index);
	if (total > lemin->nb_ants)
		return (0);
	ft_printf("nb paths = %d\n", lemin->nb_paths);
	remainder = (lemin->nb_ants - total) / lemin->nb_paths;
	ft_printf("remainder = %d\n", remainder);
	reste = lemin->nb_ants - (remainder * lemin->nb_paths + total);
	ft_printf("reste = %d\n", reste);
	while (i < index)
	{
		ft_printf("AVANT tmp->max_steps is : %d\n", tmp->max_steps);
		tmp->max_steps += (remainder + tmp->len + (reste ? 1 : 0) - 1);
		ft_printf("APRES tmp->max_steps is : %d\n", tmp->max_steps);
		if (max < tmp->max_steps)
			max = tmp->max_steps;
		tmp = tmp->next;
		i++;
		if (reste > 0)
			reste--;
	}
	max_steps = max;
	ft_printf("{green}max_steps is : %d{reset}\n", max_steps);
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
		//lemin->path_max_len = head->len;    // beware if container is better than container 1 need to change
		ft_printf("{yellow}---max len is %d{reset}\n", head->len);
		ft_printf("{red} nb paths is : %d\n{reset}", nb_paths);
	}
	return (1);
}