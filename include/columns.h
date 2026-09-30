/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   columns.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 20:19:58 by kecheong          #+#    #+#             */
/*   Updated: 2026/09/21 20:25:53 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLUMNS_H
# define COLUMNS_H

# include "entry.h"

int	calculate_max_possible_cols(int num_entries);
int	bruteforce_columns(int max_cols, struct s_entry *entries);

#endif
