/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 22:13:03 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/19 23:20:18 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filepaths.h"
#include "entry.h"
#include "ft_vec.h"
#include "options/options.h"
#include "utils.h"

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
