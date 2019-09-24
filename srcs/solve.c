/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 12:08:13 by mjouffro          #+#    #+#             */
/*   Updated: 2019/09/24 15:45:29 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_allpaths *final_solution(t_lemin *lemin)
{
	t_allpaths *tmp = NULL;

	if (lemin->max_steps <= lemin->max_steps1)
		tmp = lemin->container;
	else if (lemin->max_steps > lemin->max_steps1)
	{
		tmp = lemin->container1;
		ft_printf("tmp is container1{reset}\n");
	}
	return (tmp);
}

int		ants_per_path(t_lemin *lemin, t_allpaths *head, int max_len)
{
	t_allpaths		*tmp;
	int				total = 0;
	int				remainder = 0;
	int				reste;
	
	tmp = head;
	while (tmp)
	{
		lemin->path_max_len = tmp->len;
		tmp = tmp->next;
	}
	tmp = head;
	while (tmp)
	{
		ft_printf("{yellow}max len is %d\n{reset}", max_len);
		tmp->nb_ants = (max_len + 1) - tmp->len;
		ft_printf("tmp nb ants is %d\n", tmp->nb_ants);
		ft_printf("tmp len is %d\n", tmp->len);
		total += tmp->nb_ants;
		ft_printf("total is %d\n", total);
		tmp = tmp->next;
	}
	remainder = (lemin->nb_ants - total) / lemin->nb_paths;
	ft_printf("{red}lemin nb ants is %d{reset}\n", lemin->nb_ants);
	ft_printf("{red}remainder is %d{reset}\n", remainder);
	ft_printf("{red}lemin nb paths is %d{reset}\n", lemin->nb_paths);
	reste = lemin->nb_ants - (remainder * lemin->nb_paths) - total;
	ft_printf("{yellow}reste is %d{reset}\n", reste);
	tmp = head;
	while (tmp)
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
//	head = lemin->container;
	ft_printf("{yellow}path max len is %d\n{reset}", lemin->path_max_len);
	ft_printf("{yellow}---------------------------\n\n{reset}");
	tmp = head;
	ants_per_path(lemin, tmp, lemin->path_max_len);
	move = 1;
	lemin->ant_state = 1;
	while (tmp)
	{
	//	tmp->nb_ants += lemin->remainder;
	//	ft_printf("{green}remaindr is :%u\n{reset}", lemin->remainder);
		ft_printf("{green}tmp len is :%u\n{reset}", tmp->len);
		ft_printf("{green}tmp nb ants is :%u\n{reset}", tmp->nb_ants);
		tmp = tmp->next;
	}
	tmp = head;
	
	
	while (move < lemin->max_steps)
		move += solve(lemin, head);
	
	//while (move)
	//	move = solve(lemin, path);
	return (1);
}

int		is_empty(t_allpaths *path)
{
	t_links			*tmp;

	tmp = path->path;
	while (tmp)
	{
		if (tmp->room->antid != 0)
			return (FAILURE);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int		solve(t_lemin *lemin, t_allpaths *path)
{
	int i;
	int	ret;
	static int left;
	t_allpaths *tmp;

	i = 0;
	left = 0;
	tmp = path;
	ret = 0;
	while (i < lemin->nb_paths)
	{
		move_ants(lemin, tmp);
		fill_ants(lemin, tmp);
		left = display_ants(tmp, left);
		ret = (is_empty(tmp) == 0) ? 1 : ret;
		tmp = tmp->next;
		//ft_printf("left is %d\n", left);
		i++;
	}
	ret == 1 ? ft_printf("\n") : 0;
	return (ret);
}

void	move_ants(t_lemin *lemin, t_allpaths *paths)
{
	t_links			*tmp;
	unsigned int	tracker;
	unsigned int	current;
	unsigned int	next;

	tmp = paths->path;
	(tmp->room->hash == lemin->hashstart) ? (tmp = tmp->next) : 0;
	current = 0;
	next = 0;
	tracker = 0;
	while (tmp)
	{
		current = tmp->room->antid;
		tmp->room->antid = tracker;
		if (tmp->next)
			next = tmp->next->room->antid;
		tracker = current;
		tmp = tmp->next;
	}
}

void	fill_ants(t_lemin *lemin, t_allpaths *paths)
{
	t_links 		*tmp;

	tmp = paths->path;
	tmp = tmp->next;
	if (tmp->room->antid == 0 && paths->nb_ants != 0)
	{
		tmp->room->antid = lemin->ant_state;
		lemin->ant_state++;
		paths->nb_ants--;
	}
	/*if (paths->nb_ants == 0)
	{
		tmp->room->antid = 0;
	}*/
}
