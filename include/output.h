/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 22:11:09 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/20 22:13:39 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_H
# define OUTPUT_H

# include "entry.h"

void	print_output(const struct s_options *options,
			struct s_entry *files, struct s_entry *dirs);
void	output_files(const struct s_entry *entries,
			const struct s_options *options);
void	output_files_long_listing(const struct s_entry *entries,
							const struct s_options *options);
void	output_directories(const struct s_entry *entries, bool have_files,
			const struct s_options *options);
void	output_directories_long_listing(struct s_entry *directories,
									bool have_files,
									const struct s_options *options);

/* Long listing formatting */

char		*stringify_file_mode(mode_t mode);
char		*get_datetime(struct timespec ts);
const char	*get_user_name(uid_t uid);
const char	*get_group_name(gid_t gid);

#endif
