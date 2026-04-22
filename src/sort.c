/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 21:00:43 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/22 20:46:13 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"
#include "entry.h"
#include "ft_vec.h"
#include "libft.h"
#include <stddef.h>

struct s_entry	*sort_by_time_inefficiently(struct s_entry *entries)
{
	size_t	i;
	size_t	j;
	size_t	bubbled;
	bool	no_swaps;
	struct s_entry	lhs;
	struct s_entry	rhs;

	i = 0;
	bubbled = 0;
	while (i < ft_vec_len(entries))
	{
		j = 0;
		no_swaps = true;
		while (j < ft_vec_len(entries) - 1 - bubbled)
		{
			lhs = entries[j];
			rhs = entries[j+1];
			if (lhs.statbuf.st_mtim.tv_sec > rhs.statbuf.st_mtim.tv_sec)
			{
				j++;
				continue;
			}
			if (lhs.statbuf.st_mtim.tv_sec < rhs.statbuf.st_mtim.tv_sec)
			{
				entries[j+1] = lhs;
				entries[j] = rhs;
				no_swaps = false;
			}
			else if (lhs.statbuf.st_mtim.tv_sec == rhs.statbuf.st_mtim.tv_sec)
			{
				if (lhs.statbuf.st_mtim.tv_nsec < rhs.statbuf.st_mtim.tv_nsec)
				{
					entries[j+1] = lhs;
					entries[j] = rhs;
					no_swaps = false;
				}
			}
			j++;
		}
		if (no_swaps)
		{
			break;
		}
		i++;
	}
	return (entries);
}

struct s_entry	*sort_alphabetically_inefficiently(struct s_entry *entries)
{
	size_t	i;
	size_t	j;
	size_t	bubbled;
	bool	no_swaps;
	struct s_entry	lhs;
	struct s_entry	rhs;

	i = 0;
	bubbled = 0;
	while (i < ft_vec_len(entries))
	{
		j = 0;
		no_swaps = true;
		while (j < ft_vec_len(entries) - 1 - bubbled)
		{
			lhs = entries[j];
			rhs = entries[j+1];
			if (ft_strcmp(lhs.name, rhs.name) > 0)
			{
				entries[j+1] = lhs;
				entries[j] = rhs;
				no_swaps = false;
			}
			j++;
		}
		if (no_swaps)
		{
			break;
		}
		i++;
	}
	return (entries);
}

t_sorter	pick_sorting_algorithm(const struct s_options *options)
{
	if (is_option_enabled(options, "t"))
	{
		return (sort_by_time_inefficiently);
	}
	else
	{
		return (sort_alphabetically_inefficiently);
	}
}
