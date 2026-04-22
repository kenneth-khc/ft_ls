/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_directories.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 20:17:03 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/22 20:25:38 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "directory.h"
#include "ft_printf.h"
#include "ft_vec.h"
#include "entry.h"
#include "options/options.h"
#include "output.h"
#include "sort.h"
#include <stdio.h>

void	output_directories(const struct s_entry *entries, bool have_files,
			const struct s_options *options)
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
		files = read_directory(&entries[0], options);
		files = sort_alphabetically_inefficiently(files);
		if (have_files)
		{
			ft_printf("%s:\n", entries[0].name);
		}
		output_files(files, options);
		ft_vec_free(files);
	}
	else
	{
		while (i < num_dirs)
		{
			files = read_directory(&entries[i], options);
			sort_alphabetically_inefficiently(files);
			ft_printf("%s:\n", entries[i].name);
			output_files(files, options);
			if (i != num_dirs - 1)
			{
				ft_printf("\n");
			}
			ft_vec_free(files);
			i++;
		}
	}
}

void	output_directories_long_listing(struct s_entry *directories,
									bool have_files,
									const struct s_options *options)
{
	const size_t	num_dirs = ft_vec_len(directories);
	struct s_entry	*files;
	size_t			i;

	if (have_files)
	{
		ft_printf("\n");
	}
	if (num_dirs == 1)
	{
		files = read_directory(&directories[0], options);
		files = sort_alphabetically_inefficiently(files);
		if (have_files)
		{
			ft_printf("%s:\n", directories[0].name);
		}
		ft_printf("total %u\n", count_blocks_allocated(files));
		output_files_long_listing(files, options);
		ft_vec_free(files);
	}
	else
	{
		i = 0;
		while (i < num_dirs)
		{
			files = read_directory(&directories[i], options);
			files = sort_alphabetically_inefficiently(files);
			ft_printf("%s:\n", directories[i].name);
			ft_printf("total %u\n", count_blocks_allocated(files));
			output_files_long_listing(files, options);
			if (i != num_dirs - 1)
			{
				ft_printf("\n");
			}
			ft_vec_free(files);
			i++;
		}
	}
}
