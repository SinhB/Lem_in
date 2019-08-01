#include "lem_in.h"

int		start_end(char *line)
{
	if (ft_strcmp("##start", line) == 0)
		return (S_START);
	else if (ft_strcmp("##end", line) == 0)
		return (S_END);
	return (FAILURE);
}

int		gnl_exit(char *line)
{
	ft_strdel(&line);
	return (0);
}

int		parsing(t_lemin *lemin)
{
	char		*line;

	line = NULL;
	while (get_next_line(FD, &line) == 1)
	{
		if (is_command(line))
		{
			lemin->state |= start_end(line);
			add_line_to_str(lemin, line);
		}
		else if (is_comment(line))
		{
			add_line_to_str(lemin, line);
			ft_strdel(&line);
		}
		else if (ft_str_is_digit(line) && !lemin->nb_ants)
			lemin->nb_ants = ft_atoi(line);
		else if (ft_strchr(line, '-') && (lemin->state & S_ROOMS))
		{
			if (rooms_errors(lemin) && !(lemin->state & S_LINKS))
				return (gnl_exit(line));
			if (!get_link(lemin, &lemin->list, line))
				return (gnl_exit(line));
		}
		else if (!(lemin->state & S_LINKS) && is_room(line) 
			&& (lemin->nb_ants))
		{
			if (!get_room(lemin, &lemin->list, line))
				return (gnl_exit(line));
		}
		else
			return (gnl_exit(line));
		ft_strdel(&line);
	}
	return (1);
}

// declare 2 t_links => the temporary queue of the rooms
// 			         => the new element you want to add
// malloc the new element -> new_elem->room = malloc_graph
// set(&(elem->room),line) the  name for new elem -> name
// add this element to the temporary queue of the rooms
