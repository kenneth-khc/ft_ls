/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 22:10:19 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/30 18:20:47 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"
#include "entry.h"
#include "options/options.h"
#include "ft_vec.h"
#include "ft_printf.h"
#include "printer.h"
#include <stdlib.h>

void	print_file_long_listing(const struct s_entry *file)
{
	const struct stat	*sb;
	char				*file_mode;
	char				*datetime;

	sb = &file->statbuf;
	file_mode = stringify_file_mode(sb->st_mode);
	datetime = get_datetime(sb->st_mtim);
	ft_printf("%s %u %s %s %u %s %s\n",
			file_mode,
			file->statbuf.st_nlink,
			get_user_name(sb->st_uid),
			get_group_name(sb->st_gid),
			sb->st_size,
			datetime,
			file->name);
	free(file_mode);
	free(datetime);
}

void	output_files_long_listing(const struct s_entry *files,
							const struct s_options *options,
								  struct s_printer *printer)
{
	(void)options;
	(void)printer;
	size_t	i;
	const struct stat	*sb;
	char				*file_mode;
	char				*datetime;

	i = 0;
	while (i < ft_vec_len(files))
	{
		sb = &files[i].statbuf;
		file_mode = stringify_file_mode(sb->st_mode);
		datetime = get_datetime(sb->st_mtim);
		ft_printf("%s %u %s %s %u %s %s\n",
				file_mode,
				files[i].statbuf.st_nlink,
				get_user_name(sb->st_uid),
				get_group_name(sb->st_gid),
				sb->st_size,
				datetime,
				files[i].name);
		free(file_mode);
		free(datetime);
		i++;
	}
	ft_printf("\n");
	// require_newline(printer);
}
