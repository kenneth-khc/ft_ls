/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 22:11:09 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/18 17:55:29 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_H
# define OUTPUT_H

# include "entry.h"

void	print_output(struct s_entry *files, struct s_entry *dirs);
void	output_files(const struct s_entry *entries);
void	output_directories(const struct s_entry *entries, bool have_files);

/* Long listing formatting */

char		*stringify_file_mode(mode_t mode);
char		*get_datetime(struct timespec ts);
const char	*get_user_name(uid_t uid);
const char	*get_group_name(gid_t gid);

#endif
