## ======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============ ##
#
# Účel:		IOS – projekt 2 (synchronizace)
#
# $NoKeywords: $IOS_proj2 $Makefile
# $Author:     Iveta Snášelová <xsnase07@stud.fit.vutbr.cz>
# $Date:       $2021-05-01
## ============================================================================ ##
##
 # @file	Makefile
 # @author	Iveta Snášelová
 #
 # @brief	Implementace Makefile
##

CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -Werror -pedantic

proj2: proj2.c
	$(CC) $(CFLAGS) $^ -o $@ -lpthread

clean:
	rm -f proj2

zip:
	zip xsnase07.zip *c *h Makefile