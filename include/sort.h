/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 21:01:58 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/22 20:45:22 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_H
# define SORT_H

# include "options/options.h"

typedef struct s_entry *(*t_sorter)(struct s_entry*);

t_sorter		pick_sorting_algorithm(const struct s_options *options);
struct s_entry	*sort_alphabetically_inefficiently(struct s_entry *entries);
struct s_entry	*sort_by_time_inefficiently(struct s_entry *entries);

#endif
