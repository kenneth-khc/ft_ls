/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 22:09:05 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/22 20:23:17 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIRECTORY_H
# define DIRECTORY_H

#include "options/options.h"
# include <sys/types.h>

struct s_entry	*read_directory(const struct s_entry *directory,
					const struct s_options *options);
blkcnt_t		count_blocks_allocated(const struct s_entry *files);

#endif
