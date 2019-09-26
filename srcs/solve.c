/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 12:08:13 by mjouffro          #+#    #+#             */
/*   Updated: 2019/09/26 16:35:55 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_allpaths *final_solution(t_lemin *lemin)
{
	t_allpaths *tmp = NULL;

	if (lemin->max_steps <= lemin->max_steps1)
	{
		tmp = lemin->container;
		lemin->nb_paths = lemin->nb_pathsbfs;
	}
	else if (lemin->max_steps > lemin->max_steps1)
	{
		tmp = lemin->container1;
		lemin->nb_paths = lemin->nb_pathsek;
		ft_printf("{green}tmp is container1{reset}\n");
	}
	ft_printf("========== nbpaths is : %u", lemin->nb_paths);
	return (tmp);
}

int		ants_per_path(t_lemin *lemin, t_allpaths *head)
{
	t_allpaths		*tmp;
	int				total = 0;
	int				remainder = 0;
	int				reste;
	
	tmp = head;
	while (tmp->next != NULL)
	{
		lemin->path_max_len = tmp->len;
		ft_printf("{red}max path len is %d\n{reset}", tmp->len);
		tmp = tmp->next;
	}
	tmp = head;
	while (tmp->next != NULL)
	{
		ft_printf("----------------------\n");
		ft_printf("{yellow}max len is %d\n{reset}", lemin->path_max_len);
		//tmp->nb_ants = (lemin->path_max_len - tmp->len + 1);

		tmp->nb_ants = (lemin->path_max_len - tmp->len + 1);
		ft_printf("tmp nb ants is %d\n", tmp->nb_ants);
		ft_printf("tmp len is %d\n", tmp->len);
		total += tmp->nb_ants;
		tmp = tmp->next;
		ft_printf("----------------------\n");
	}
	ft_printf("{yellow}lemin nb ants is {red}%d{reset}\n", lemin->nb_ants);
	ft_printf("{yellow}total is {red}%d{reset}\n", total);
	ft_printf("{yellow}lemin nb paths is {red}%d{reset}\n", lemin->nb_paths);
	remainder = (lemin->nb_ants - total) / lemin->nb_paths;
	ft_printf("{yellow}remainder is {red}%d{reset}\n", remainder);
	reste = lemin->nb_ants - (remainder * lemin->nb_paths) - total;
	ft_printf("{yellow}reste is %d{reset}\n", reste);
	tmp = head;
	while (tmp->next != NULL)
	{
		tmp->nb_ants += remainder;
		tmp->nb_ants += reste ? 1 : 0;
		reste > 0 ? reste-- : 0;
		tmp = tmp->next;
	}
	return (0);
}

int		solve_lemin(t_lemin *lemin, unsigned int move)
{
	t_allpaths *head;
	t_allpaths *tmp;
	
	head = final_solution(lemin);
	//head = lemin->container;
//	ft_printf("{yellow}path max len is %d\n{reset}", lemin->path_max_len);
	ft_printf("{yellow}---------------------------\n\n{reset}");
	
	tmp = head;

	ants_per_path(lemin, tmp);
	move = 1;
	tmp = head;
	lemin->ant_state = 1;
	//while (tmp->next != NULL)
	while (tmp)
	{
	//	tmp->nb_ants += lemin->remainder;
	//	ft_printf("{green}remaindr is :%u\n{reset}", lemin->remainder);
		ft_printf("{green}tmp len is :%u\n{reset}", tmp->len);
		ft_printf("{green}tmp nb ants is :%u\n{reset}", tmp->nb_ants);
		tmp = tmp->next;
	}
	tmp = head;
	ft_printf("{red}--------lemin->maxsteps is %d---------\n{reset}", lemin->max_steps);
	while (move <= lemin->max_steps)
		move += move_and_display(lemin, head);
	return (1);
}




