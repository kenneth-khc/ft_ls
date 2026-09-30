/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_directories.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 20:17:03 by kecheong          #+#    #+#             */
/*   Updated: 2026/09/30 20:21:36 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "directory.h"
#include "ft_printf.h"
#include "ft_vec.h"
#include "entry.h"
#include "options/options.h"
#include "output.h"
#include "printer.h"
#include "sort.h"

void	output_directory(struct s_entry *directory,
						 const struct s_options *options,
						 struct s_printer *printer)
{
	struct s_entry	*files;
	const t_sorter	sort = pick_sorting_algorithm(options);
	bool			want_reversed = is_option_enabled(options, "r");

	files = read_directory(directory, options);
	sort(files);
	if (want_reversed)
	{
		ft_vec_reverse(files);
	}
	// maybe_print_newline(printer);
	// maybe_print_directory_prefix(printer, directory->name);
	// output_files(files, options, printer);
	print_directory(printer, directory, files);
	ft_vec_free(files);
	// ft_printf("\n");
	// require_newline(printer);
}

void	output_directory_long_listing(struct s_entry *directory,
									  const struct s_options *options,
									  struct s_printer *printer)
{
	struct s_entry	*files;
	const t_sorter	sort = pick_sorting_algorithm(options);
	const bool		want_reversed = is_option_enabled(options, "r");

	files = read_directory(directory, options);
	sort(files);
	if (want_reversed)
	{
		ft_vec_reverse(files);
	}
	maybe_print_newline(printer);
	maybe_print_directory_prefix(printer, directory->name);
	ft_printf("total %u\n", count_blocks_allocated(files));
	output_files_long_listing(files, options, printer);
	// ft_printf("\n");
	ft_vec_free(files);
}
