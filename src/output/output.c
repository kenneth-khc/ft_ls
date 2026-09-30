/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 22:07:42 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/30 18:28:12 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entry.h"
#include "ft_vec.h"
#include "options/options.h"
#include "sort.h"
#include "output.h"
#include "printer.h"
#include <stddef.h>
#include "ft_printf.h"

void	print_files(struct s_entry *files,
					const struct s_options *options,
					struct s_printer *printer)
{
	size_t			i;
	const bool		want_long_list = is_option_enabled(options, "l");
	const bool		want_reversed = is_option_enabled(options, "r");
	const t_sorter	sorter = pick_sorting_algorithm(options);
	(void)want_long_list;
	(void)printer;

	files = sorter(files);
	if (want_reversed)
	{
		ft_vec_reverse(files);
	}
	i = 0;
	while (i < ft_vec_len(files))
	{
		i++;
	}
	// if (want_long_list)
	// {
	// 	output_files_long_listing(files, options, printer);
	// }
	// else
	// {
	// 	output_files(files, options, printer);
	// }
	// ft_printf("\n");
}

// void	print_output(const struct s_options *options,
// 			struct s_entry *files, struct s_entry *dirs)
// {
// 	const bool	have_files = ft_vec_len(files) > 0;
// 	const bool	have_dirs = ft_vec_len(dirs) > 0;
// 	bool		want_long_list = is_option_enabled(options, "l");
// 	bool		want_reversed = is_option_enabled(options, "r");
// 	t_sorter	sort = pick_sorting_algorithm(options);

// 	if (want_long_list)
// 	{
// 		if (have_files)
// 		{
// 			files = sort(files);
// 			if (want_reversed)
// 			{
// 				ft_vec_reverse(files);
// 			}
// 			output_files_long_listing(files, options, NULL);
// 		}
// 		if (have_dirs)
// 		{
// 			dirs = sort(dirs);
// 			if (want_reversed)
// 			{
// 				ft_vec_reverse(dirs);
// 			}
// 			output_directories_long_listing(dirs, have_files, options, NULL);
// 		}
// 	}
// 	else
// 	{
// 		if (have_files)
// 		{
// 			files = sort(files);
// 			if (want_reversed)
// 			{
// 				ft_vec_reverse(files);
// 			}
// 			output_files(files, options, NULL);
// 		}
// 		if (have_dirs)
// 		{
// 			dirs = sort(dirs);
// 			if (want_reversed)
// 			{
// 				ft_vec_reverse(dirs);
// 			}
// 			output_directories(dirs, have_files, options, NULL);
// 		}
// 	}
// }
