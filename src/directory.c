/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 22:09:34 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/22 20:27:06 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entry.h"
#include "ft_vec.h"
#include "libft.h"
#include "options/options.h"
#include "utils.h"
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>

void	free_entry(void *entry)
{
	struct s_entry	*file;

	file = (struct s_entry *)entry;
	free(file->name);
}

struct s_entry *read_directory(const struct s_entry *directory,
							const struct s_options *options)
{
	struct s_entry	*files;
	struct s_entry	file;
	DIR				*dir;
	struct dirent	*dir_ent;
	char			*abs_filepath;
	bool			want_all;

	want_all = is_option_enabled(options, "a");
	files = ft_vec_init(sizeof (*files));
	ft_vec_set_destructor(files, free_entry);
	dir = opendir(directory->name);
	if (dir == NULL)
	{
		perror("opendir()");
		ft_panic(1, NULL);
	}
	dir_ent = readdir(dir);
	while (dir_ent != NULL)
	{
		abs_filepath = ft_strjoin_multiple(3, directory->name, "/", dir_ent->d_name);
		if (!want_all && ft_str_startswith(dir_ent->d_name, "."))
		{
			free(abs_filepath);
			dir_ent = readdir(dir);
			continue;
		}
		file.name = ft_strdup(dir_ent->d_name);
		if (stat(abs_filepath, &file.statbuf) == -1)
		{
			handle_stat_errors(abs_filepath);
		}
		files = ft_vec_append(files, &file);
		free(abs_filepath);
		dir_ent = readdir(dir);
	}
	closedir(dir);
	return (files);
}

/*
	POSIX specifies a block to be 512-byte units, identical to what is
	returned in stat.st_blocks, but GNU uses 1024-byte units, therefore
	we have to sum up stat.st_blocks and divide by 2 to match GNU's output
*/
// TODO(kecheong): this could be accumulated as we stat() through our entries
// instead of taking another pass through it afterwards
blkcnt_t	count_blocks_allocated(const struct s_entry *files)
{
	size_t					i;
	blkcnt_t				total_blocks;
	const struct s_entry	*file;

	i = 0;
	total_blocks = 0;
	while (i < ft_vec_len(files))
	{
		file = &files[i];
		total_blocks += file->statbuf.st_blocks;
		i++;
	}
	total_blocks /= 2;
	return (total_blocks);
}
