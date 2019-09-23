/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 12:59:29 by mjouffro          #+#    #+#             */
/*   Updated: 2019/09/19 16:04:29 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		display_ants(t_allpaths	*paths, int left)
{
	t_links	*tmp;

	tmp = paths->path;
	while (tmp)
	{
		if (tmp->room->antid && left == 0)
		{
			ft_printf("L%u-%s", tmp->room->antid, tmp->room->name);
			left = 1;
		}
		else if (tmp->room->antid && left == 1)
			ft_printf(" L%u-%s", tmp->room->antid, tmp->room->name);
		tmp = tmp->next;
	}
	return (left);
}

/*

# define S_START_TO_END (1 << 4)

int		display_ants(t_allpaths	*paths, int left)
{
	if ()
}


int		head_linked_to_sink(int head, int sink)
{
	return (lemin->matrix[head][sink]);
}


int			start_directly_linked_to_end(t_lemin *lemin)
{
	if (head_linked_to_sink(lemin->head->id, lemin->sink->id))
	{
		lemin->state |= S_START_TO_END;
		return (1);
	}
	return (0);
}


static void	print_path(t_env *env, t_room *start)
{
	ft_printf("%s\t", env->start->name);
	while (start != env->end)
	{
		ft_printf("%s\t", start->name);
		start = start->next;
	}
	ft_printf("%s\n", env->end->name);
}

void		print_paths(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->nb_rooms)
	{
		if (env->matrix[env->start->id][i]
				&& (env->rooms_array[i]->flag & FL_CLOSE_PATH))
			print_path(env, env->rooms_array[i]);
		++i;
	}
}

static void	print_paths_array(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->nb_paths)
	{
		ft_printf("%d: (%d, %s, %d)", i, env->paths_array[i]->length,
				env->paths_array[i]->back->name,
				env->paths_array[i]->nb_ants_stream);
		if (i < env->nb_paths - 1)
			ft_printf(" | ");
		i++;
	}
	ft_putchar('\n');
}

static void	print_ants_move_start_end(t_env *env)
{
	int		i;

	i = 1;
	while (i <= env->nb_ants)
	{
		ft_printf("L%d-%s", i, env->end->name);
		if (i < env->nb_ants)
			ft_putchar(' ');
		++i;
	}
	ft_putchar('\n');
}

void		print_output(t_env *env)
{
	print_lines(env->lines);
	ft_putchar('\n');
	if (env->start->flag & FL_DIRECT_TO_END)
		print_ants_move_start_end(env);
	else
	{
		print_all_lines_of_ants_moves(env);
		if (env->options & OP_DEBUG)
		{
			ft_printf("\nNb of ants: %d\n", env->nb_ants);
			ft_printf("\nPaths found:\n");
			print_paths(env);
			ft_printf("\nPaths ordered:\n");
			print_paths_array(env);
		}
	}
}
*/