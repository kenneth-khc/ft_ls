/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 23:48:22 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/22 20:30:10 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options/options.h"
#include "filepaths.h"
#include "ft_vec.h"
#include <stddef.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include "entry.h"
#include "output.h"

int	main(int argc, char **argv)
{
	struct s_options	options;
	struct s_filepath	*filepaths;
	struct s_entry		*files;
	struct s_entry		*directories;

	(void)argc;
	errno = 0;
	options = init_program_options();
	filepaths = parse_args(++argv, &options);
	if (ft_vec_len(filepaths) == 0)
	{
		filepaths = ft_vec_append(filepaths, &(struct s_filepath){.str = "."});
	}

	files = ft_vec_init(sizeof *files);
	directories = ft_vec_init(sizeof *directories);
	get_entries(filepaths, &options, &files, &directories);
	print_output(&options, files, directories);

	ft_vec_free(filepaths);
	ft_vec_free(files);
	ft_vec_free(directories);
}
