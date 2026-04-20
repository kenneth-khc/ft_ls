/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_long_listing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:36:54 by kecheong          #+#    #+#             */
/*   Updated: 2026/04/20 22:13:30 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/stat.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "libft.h"

const char	*stringify_entry_type(mode_t mode)
{
	const char	*entry_type = NULL;

	if (S_ISREG(mode))
	{
		entry_type = "-";
	}
	else if (S_ISDIR(mode))
	{
		entry_type = "d";
	}
	else if (S_ISCHR(mode))
	{
		entry_type = "c";
	}
	else if (S_ISBLK(mode))
	{
		entry_type = "b";
	}
	else if (S_ISLNK(mode))
	{
		entry_type = "l";
	}
	else if (S_ISFIFO(mode))
	{
		entry_type = "p";
	}
	else if (S_ISSOCK(mode))
	{
		entry_type = "s";
	}
	return (entry_type);
}

char	*stringify_owner_permissions(mode_t mode)
{
	char	buf[4];

	buf[3] = '\0';
	ft_memset(buf, '-', 3);
	if (mode & S_IRUSR)
	{
		buf[0] = 'r';
	}
	if (mode & S_IWUSR)
	{
		buf[1] = 'w';
	}
	if (mode & S_ISUID)
	{
		if (mode & S_IXUSR)
		{
			buf[2] = 's';
		}
		else if (!(mode & S_IXUSR))
		{
			buf[2] = 'S';
		}
	}
	else if (mode & S_IXUSR)
	{
		buf[2] = 'x';
	}
	return (ft_strdup(buf));
}

char	*stringify_group_permissions(mode_t mode)
{
	char	buf[4];

	buf[3] = '\0';
	ft_memset(buf, '-', 3);
	if (mode & S_IRGRP)
	{
		buf[0] = 'r';
	}
	if (mode & S_IWGRP)
	{
		buf[1] = 'w';
	}
	if (mode & S_ISGID)
	{
		if (mode & S_IXGRP)
		{
			buf[2] = 's';
		}
		else
		{
			buf[2] = 'S';
		}
	}
	else if (mode & S_IXGRP)
	{
		buf[2] = 'x';
	}
	return (ft_strdup(buf));
}

char	*stringify_other_permissions(mode_t mode)
{
	char	buf[4];

	buf[3] = '\0';
	ft_memset(buf, '-', 3);
	if (mode & S_IROTH)
	{
		buf[0] = 'r';
	}
	if (mode & S_IWOTH)
	{
		buf[1] = 'w';
	}
	if (S_ISDIR(mode) && (mode & S_ISVTX))
	{
		if (mode & S_IXOTH)
		{
			buf[2] = 't';
		}
		else
		{
			buf[2] = 'T';
		}
	}
	else if (mode & S_IXOTH)
	{
		buf[2] = 'x';
	}
	return (ft_strdup(buf));
}

const char	*get_user_name(uid_t uid)
{
	struct passwd	*pws;

	pws = getpwuid(uid);
	if (pws == NULL)
	{
		// TODO: handle errors
		return (NULL);
	}
	else
	{
		return (pws->pw_name);
	}
}

const char	*get_group_name(gid_t gid)
{
	const struct group	*grp;

	grp = getgrgid(gid);
	if (grp == NULL)
	{
		// TODO: handle errors
		return (NULL);
	}
	else
	{
		return (grp->gr_name);
	}
}

// "%c%s%s%s%c", <entry type>, <owner permissions>,
//     <group permissions>, <other permissions>,
//     <optional alternate access method flag>	if (S_ISREG(mode))
// d
//     Directory.
// b
//     Block special file.
// c
//     Character special file.
// l (ell)
//     Symbolic link.
// p
//     FIFO.
// -
//     Regular file.

// TODO(kecheong): investigate these in more detail
char	*stringify_file_mode(mode_t mode)
{
	const char	*entry_type = stringify_entry_type(mode);
	char		*owner_permissions =  stringify_owner_permissions(mode);
	char		*group_permissions =  stringify_group_permissions(mode);
	char		*other_permissions =  stringify_other_permissions(mode);
	char		*file_mode_string;

	file_mode_string = ft_strjoin_multiple(4,
										entry_type,
										owner_permissions,
										group_permissions,
										other_permissions);
	free(owner_permissions);
	free(group_permissions);
	free(other_permissions);
	return (file_mode_string);
}

char	*get_datetime_for_non_recent_file(const char *time_string)
{
	char	*month_and_day = ft_substr(time_string, 4, 6);
	char	*year = ft_substr(time_string, ft_strlen(time_string) - 5, 4);
	char	*formatted_non_recent_datetime;

	formatted_non_recent_datetime =
		ft_strjoin_multiple(3, month_and_day, "  ", year);
	free(month_and_day);
	free(year);
	return (formatted_non_recent_datetime);
}

#define SIX_MONTHS_IN_SECONDS 15768000

char	*get_datetime(struct timespec ts)
{
	const time_t	seconds_elapsed = ts.tv_sec;
	const time_t	seconds_elapsed_now = time(NULL);
	const char		*time_string = ctime(&seconds_elapsed);

	if (seconds_elapsed_now - seconds_elapsed > SIX_MONTHS_IN_SECONDS)
	{
		return get_datetime_for_non_recent_file(time_string);
	}
	else
	{
		return ft_substr(time_string, 4, ft_strlen(time_string) - 13);
	}
}
