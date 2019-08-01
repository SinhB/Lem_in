/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sharing_ants.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 11:43:03 by yabecret          #+#    #+#             */
/*   Updated: 2019/07/05 19:38:42 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

unsigned int	get_total_len(t_lemin *lemin)
{
	t_allpaths		*tmp;
	unsigned int	ret;

	ret = 0;
	tmp = lemin->container;
	while (tmp->next)
	{
		//ft_printf ("tmp->len is : %u\n", tmp->len);
		if (tmp->len == 0)
			lemin->nb_paths--;
		ret += tmp->len;
		tmp = tmp->next;
	}
	return (ret);
}

/*unsigned int	fill_path(t_lemin *lemin, t_allpaths *allpaths, unsigned int *len)
{
	unsigned int n;

	n = 0;
	return(lemin->nb_ants - (((lemin->nb_paths - 1) * allpaths->len) - (len - allpaths->len))) / lemin->nb_paths);
	while (((allpaths->len - 1) + n < max_steps) && (sous_total + n < nb_ants))
		n++;
	return (n);
}*/

//(ant_nb    -      (   ((n_paths - 1) * path_len)     -     (total_len - path_len)   )    ) / n_paths;

int				sharing_ants(t_lemin *lemin)
{
	unsigned int	total_len;
	unsigned int	sous_total;
	unsigned int	tmp;
	t_allpaths		*allpaths;

	tmp = 0;
	sous_total = 0;
	total_len = get_total_len(lemin);
	//ft_printf ("{green}total_len is : %u\n{reset}", total_len);
	//lemin->max_steps = (lemin->nb_ants + total_len - 1) / lemin->nb_paths;
	//lemin->max_steps = 75;
	//ft_printf ("{green}max_steps is : %u\n{reset}", lemin->max_steps);
	allpaths = lemin->container;
	while (allpaths->next)
	{
		//allpaths->nb_ants = fill_path(lemin, allpaths, total_len);
		allpaths->nb_ants = (lemin->nb_ants - (((lemin->nb_paths - 1) * allpaths->len) - (total_len - allpaths->len))) / lemin->nb_paths;
		if (allpaths->nb_ants > lemin->nb_ants)
			allpaths->nb_ants = 0;
		ft_printf ("{green}allpaths->len is : %u\n{reset}", allpaths->len);
		ft_printf ("{green}allpaths->nb_ants is : %u\n{reset}", allpaths->nb_ants);
		sous_total += allpaths->nb_ants;
		if (lemin->nb_paths == 1 && lemin->nb_ants != sous_total)
			allpaths->nb_ants += (lemin->nb_ants - sous_total);
		ft_printf ("sous_total is : %u\n", sous_total);
		allpaths = allpaths->next;
	}
	allpaths = lemin->container;
	while (lemin->nb_ants > sous_total)
	{
		while (allpaths->next)
		{
			ft_printf("lemin nb ants is : %d\n", lemin->nb_ants);
			if (allpaths->nb_ants != 0 && lemin->nb_ants > allpaths->nb_ants)
			{
				allpaths->nb_ants += 1;
				sous_total++;
			}
			ft_printf ("{green}allpaths->len is : %u\n{reset}", allpaths->len);
			ft_printf ("{green}allpaths->nb_ants is : %u\n{reset}", allpaths->nb_ants);
			if (sous_total == lemin->nb_ants)
				break ;
			allpaths = allpaths->next;
		}
	}
	ft_printf ("sous_total is : %u\n", sous_total);
	return (SUCCESS);
}
