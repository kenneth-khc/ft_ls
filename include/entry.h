/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 20:26:29 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/19 23:21:57 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTRY_H
# define ENTRY_H

# include "options/options.h"
# include "filepaths.h"
# include <sys/stat.h>

typedef struct s_entry
{
	char		*name;
	struct stat	statbuf;
}	t_entry;

void	get_entries(const struct s_filepath *filepaths,
			struct s_options *options,
			struct s_entry **files, struct s_entry **directories);

#endif
