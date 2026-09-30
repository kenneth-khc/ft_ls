/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 22:13:03 by kecheong          #+#    #+#             */
/*   Updated: 2026/09/30 20:21:17 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filepaths.h"
#include "entry.h"
#include "ft_vec.h"
#include "options/options.h"
#include "output.h"
#include "sort.h"
#include "utils.h"
#include "printer.h"

void	process_file_entries(struct s_entry *files,
							 struct s_options *options,
							 struct s_printer *printer)
{
	const bool		want_reversed = is_option_enabled(options, "r");
	const t_sorter	sort = pick_sorting_algorithm(options);

	sort(files);
	if (want_reversed)
	{
		ft_vec_reverse(files);
	}
	while (ft_vec_len(files) > 0)
	{
		if (printer->want_long_listing)
		{
		}
		else
		{
		}
		ft_vec_pop_front(files);
	}
}

void	process_directory_entries(struct s_entry **directories,
							struct s_options *options,
								  struct s_printer *printer)
{
	const bool		want_recursive = is_option_enabled(options, "R");
	const bool		want_reversed = is_option_enabled(options, "r");
	// const bool		want_long_listing = is_option_enabled(options, "l");
	const t_sorter	sort = pick_sorting_algorithm(options);

	if (want_recursive)
	{
	}
	else
	{
		*directories = sort(*directories);
		if (want_reversed)
		{
			ft_vec_reverse(*directories);
		}
		// maybe_print_newline(printer);
		while (ft_vec_len(*directories) > 0)
		{
			// if (want_long_listing)
			// {
			// 	// output_directories_long_listing(*directories, false,
			// 	// 							options, printer);
			// 	output_directory_long_listing(*directories, options, printer);
			// }
			// else
			// {
				output_directory((*directories), options, printer);
				// output_directories(*directories, false, options, printer);
			// }
			ft_vec_pop_front(*directories);
		}
	}
}

void	get_entries(const struct s_filepath *filepaths, struct s_options *options,
				struct s_entry **files, struct s_entry **directories)
{
	size_t		i;
	int			ret;
	char		*filename;
	struct stat	statbuf;

	i = 0;
	while (i < ft_vec_len(filepaths))
	{
		filename = filepaths[i].str;
		ret = stat(filename, &statbuf);
		if (ret == -1)
		{
			handle_stat_errors(filename);
		}
		else
		{
			// print_stat(filename, &statbuf);
			if (S_ISDIR(statbuf.st_mode))
			{
				*directories = ft_vec_append(*directories,
									&(struct s_entry){
			                        .name = filename,
			                        .statbuf = statbuf});
			}
			else
			{
				*files = ft_vec_append(*files,
										&(struct s_entry){
				                        .name = filename,
				                        .statbuf = statbuf});
			}
		}
		i++;
	}
	(void)options;
}
