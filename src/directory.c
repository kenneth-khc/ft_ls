/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 22:09:34 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/16 22:10:16 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entry.h"
#include "ft_vec.h"
#include "libft.h"
#include <stdio.h>
#include <dirent.h>

struct s_entry *read_directory(const struct s_entry *directory)
{
	struct s_entry	*files;
	struct s_entry	file;
	DIR				*dir;
	struct dirent	*dir_ent;

	files = ft_vec_init(sizeof (*files));
	dir = opendir(directory->name);
	if (dir == NULL)
	{
		perror("opendir()");
		ft_panic(1, NULL);
	}
	dir_ent = readdir(dir);
	while (dir_ent != NULL)
	{
		if (!ft_str_startswith(dir_ent->d_name, "."))
		{
			file.name = ft_strdup(dir_ent->d_name);
			files = ft_vec_append(files, &file);
		}
		dir_ent = readdir(dir);
	}
	return (files);
}
