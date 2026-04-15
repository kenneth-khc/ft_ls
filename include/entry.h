/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 20:26:29 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/15 20:27:23 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTRY_H
# define ENTRY_H

# include <sys/stat.h>

typedef struct s_entry
{
	const char	*name;
	struct stat	statbuf;
}	t_entry;

#endif
