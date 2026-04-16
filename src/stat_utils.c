/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:38:14 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/16 22:33:10 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "ft_printf.h"
#include "libft.h"
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include "time.h"
#include <stdlib.h>

void	handle_stat_errors(const char *filename)
{
	// TODO(kecheong): handle more errors

	if (errno == ENOENT)
	{
		ft_dprintf(STDERR_FILENO, "%s: cannot access '%s': "
			"No such file or directory\n", "ft_ls", filename);
	}
	else
	{
		perror("stat()");
		ft_panic(1, "");
	}
}

// void	print_stat(const char *filename, const struct stat *statbuf)
// {
// 	char	*access_time = ft_strdup(ctime(&statbuf->st_atim.tv_sec));
// 	char	*modify_time = ft_strdup(ctime(&statbuf->st_mtim.tv_sec));
// 	char	*change_time = ft_strdup(ctime(&statbuf->st_ctim.tv_sec));

// 	printf("Filename     : %s\n"
// 	       "ID of device : %ld\n"
//            "Inode num    : %ld\n"
//            "Mode         : %d\n"
//            "# hard links : %ld\n"
//            "Owner UID    : %d\n"
//            "Owner GID    : %d\n"
//            "Total bytes  : %ld\n"
//            "Block size   : %ld\n"
//            "# 512B blocks: %ld\n"
//            "Access time  : %s"
//            "Modify time  : %s"
//            "Change time  : %s",
//            filename, statbuf->st_dev, statbuf->st_ino,
//            statbuf->st_mode, statbuf->st_nlink, statbuf->st_uid,
//            statbuf->st_gid, statbuf->st_size, statbuf->st_blksize,
//            statbuf->st_blocks, access_time, modify_time, change_time);
// 	free(access_time);
// 	free(modify_time);
// 	free(change_time);
// }
