/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 22:07:42 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/22 20:40:00 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entry.h"
#include "ft_vec.h"
#include "options/options.h"
#include "sort.h"
#include "output.h"
#include <stddef.h>

void	print_output(const struct s_options *options,
			struct s_entry *files, struct s_entry *dirs)
{
	const bool	have_files = ft_vec_len(files) > 0;
	const bool	have_dirs = ft_vec_len(dirs) > 0;
	bool		want_long_list = is_option_enabled(options, "l");
	t_sorter	sort = pick_sorting_algorithm(options);

	if (want_long_list)
	{
		if (have_files)
		{
			files = sort(files);
			output_files_long_listing(files, options);
		}
		if (have_dirs)
		{
			dirs = sort(dirs);
			output_directories_long_listing(dirs, have_files, options);
		}
	}
	else
	{
		if (have_files)
		{
			files = sort(files);
			output_files(files, options);
		}
		if (have_dirs)
		{
			dirs = sort(dirs);
			output_directories(dirs, have_files, options);
		}
	}
}
