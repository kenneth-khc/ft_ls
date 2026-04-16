/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 23:48:22 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/16 22:41:19 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options/options.h"
#include "filepaths.h"
#include "ft_vec.h"
#include <stddef.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include "entry.h"
#include "sort.h"
#include "output.h"

int	main(int argc, char **argv)
{
	struct s_options	options;
	struct s_filepath	*filepaths;
	struct s_entry		*files;
	struct s_entry		*directories;

	errno = 0;
	options = init_program_options();
	if (argc == 1)
	{
		filepaths = parse_args((char*[]){".", NULL}, &options);
	}
	else
	{
		filepaths = parse_args(++argv, &options);
	}

	files = ft_vec_init(sizeof *files);
	directories = ft_vec_init(sizeof *directories);
	get_entries(filepaths, &options, &files, &directories);
	files = sort_alphabetically_inefficiently(files);
	if (ft_vec_len(files) > 0)
	{
		output_files(files);
	}
	directories = sort_alphabetically_inefficiently(directories);
	if (ft_vec_len(directories) > 0)
	{
		output_directories(directories);
	}

	ft_vec_free(filepaths);
	ft_vec_free(files);
	ft_vec_free(directories);
}
