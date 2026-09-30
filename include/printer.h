/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 21:22:11 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/30 18:16:31 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTER_H
# define PRINTER_H

# include <stdbool.h>
# include "entry.h"
# include "options/options.h"

struct s_printer
{
	bool	should_newline;
	bool	should_print_directory_prefix;
	size_t	directory_count;
	bool	want_long_listing;
};

void	set_printer_options(struct s_printer *printer,
							struct s_options *options,
							struct s_entry *directories,
							struct s_entry *files);

void	require_newline(struct s_printer *printer);
void	maybe_print_newline(struct s_printer *printer);
void	maybe_print_directory_prefix(struct s_printer *printer, const char *dir_name);

void	print_directory(struct s_printer *printer,
						struct s_entry *directory,
						struct s_entry *files);
void	print_file_long_listing(const struct s_entry *file);

#endif
