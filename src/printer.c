/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 21:34:55 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/30 18:18:33 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printer.h"
#include "ft_printf.h"
#include "ft_vec.h"
#include "options/options.h"
#include "directory.h"
#include "output.h"

void	set_printer_options(struct s_printer *printer,
							struct s_options *options,
							struct s_entry *directories,
							struct s_entry *files)
{
	const size_t	num_dirs = ft_vec_len(directories);
	const size_t	num_files = ft_vec_len(files);

	printer->directory_count = num_dirs;
	printer->want_long_listing = is_option_enabled(options, "l");
	if (num_files > 1 || num_dirs > 1)
	{
		printer->should_print_directory_prefix = true;
	}
}

void	require_newline(struct s_printer *printer)
{
	if (printer)
	{
		printer->should_newline = true;
	}
}

void	maybe_print_newline(struct s_printer *printer)
{
	if (printer == 0)
	{
		return ;
	}
	if (printer->should_newline)
	{
		ft_printf("\n");
		printer->should_newline = false;
	}
}

void	maybe_print_directory_prefix(struct s_printer *printer,
									 const char *dir_name)
{
	if (printer)
	{
		if (printer->should_print_directory_prefix)
		{
			ft_printf("%s:\n", dir_name);
		}
	}
}

void	print_directory(struct s_printer *printer,
						struct s_entry *directory,
						struct s_entry *files)
{
	size_t			i;
	static size_t	directories_printed = 0;
	const size_t	file_count = ft_vec_len(files);
	const struct s_entry	*file;

	maybe_print_directory_prefix(printer, directory->name);
	if (printer->want_long_listing)
	{
		ft_printf("total %u\n", count_blocks_allocated(files));
	}
	i = 0;
	while (i < file_count)
	{
		file = &files[i];
		i++;
		if (printer->want_long_listing)
		{
			// output_files_long_listing(files, NULL, printer);
			print_file_long_listing(file);
		}
		else
		{
			ft_printf("%s", file->name);
			if (i < file_count)
			{
				ft_printf("  ");
			}
		}
	}
	ft_printf("\n");
	directories_printed++;
	if (directories_printed < printer->directory_count)
	{
		ft_printf("\n");
	}
}
