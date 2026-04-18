/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 22:07:42 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/18 17:57:09 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "entry.h"
#include "ft_vec.h"
#include "sort.h"
#include "directory.h"
#include "output.h"
#include <stddef.h>

void	print_output(struct s_entry *files, struct s_entry *dirs)
{
	const bool	have_files = ft_vec_len(files) > 0;
	const bool	have_dirs = ft_vec_len(dirs) > 0;

	if (have_files)
	{
		files = sort_alphabetically_inefficiently(files);
		output_files(files);
	}
	if (have_dirs)
	{
		dirs = sort_alphabetically_inefficiently(dirs);
		output_directories(dirs, have_files);
	}
}

void	output_files(const struct s_entry *entries)
{
	size_t	i;

	i = 0;
	while (i < ft_vec_len(entries))
	{
		ft_printf("%s  ", entries[i].name);
		i++;
	}
	ft_printf("\n");
}

void	output_directories(const struct s_entry *entries, bool have_files)
{
	size_t			i;
	const size_t	num_dirs = ft_vec_len(entries);
	struct s_entry	*files;

	i = 0;
	if (have_files)
	{
		ft_printf("\n");
	}
	if (num_dirs == 1)
	{
		files = read_directory(&entries[0]);
		files = sort_alphabetically_inefficiently(files);
		if (have_files)
		{
			ft_printf("%s:\n", entries[0].name);
		}
		output_files(files);
	}
	else
	{
		while (i < num_dirs)
		{
			files = read_directory(&entries[i]);
			sort_alphabetically_inefficiently(files);
			ft_printf("%s:\n", entries[i].name);
			output_files(files);
			if (i != num_dirs - 1)
			{
				ft_printf("\n");
			}
			i++;
		}
	}
}
