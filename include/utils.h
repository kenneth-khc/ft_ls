/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:39:47 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/15 19:40:18 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/stat.h>

void	handle_stat_errors(const char *filename);
void	print_stat(const char *filename, const struct stat *statbuf);

#endif
