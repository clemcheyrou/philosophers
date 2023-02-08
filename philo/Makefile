# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/18 16:06:22 by adegain           #+#    #+#              #
#    Updated: 2023/02/03 18:55:16 by ccheyrou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

MAIN = 	srcs/main.c \
		srcs/thread.c \
		srcs/time.c \
		srcs/init.c \
		srcs/utils.c \
		srcs/death.c \
		srcs/eats.c

#---------------------
CC = gcc
HDR_PATH = include/
SRCS_PATH = srcs/
SRCS = ${MAIN}
CCH_PATH = obj/
FLAGS = -Wall -Werror -Wextra -g3 -I ${HDR_PATH} 
#=====================

# ------ Colors ------
RED:="\033[1;31m"
GREEN:="\033[1;32m"
PURPLE:="\033[1;35m"
CYAN:="\033[1;36m"
EOC:="\033[0;0m"
# ====================

#--- Compilation ----
SRC:= $(addprefix $(SRCS_PATH), $(SRCS))
OBJ:=$(addprefix $(CCH_PATH), $(addsuffix .o, $(SRCS)))
CCHF:=.cache_exists
#====================

all:			${NAME}

${NAME}:		${OBJS} ${SRCS}
				@echo ${CYAN} " - Compiling $@" ${EOC}
				@${CC} ${FLAGS} ${SRCS} ${OBJS} -o ${NAME} -lpthread
				@${SUPP}
				@echo ${GREEN} " - OK" ${EOC}

${CCHPATH}%.o: ${SRCPATH}%.c | ${CCHF}
				@echo ${PURPLE} " - Compiling $< into $@" ${EOC}
				@${CC} ${FLAGS} -c $< -o $@

%.c:
				@echo ${RED} "Missing file: $@" ${EOC}
				
$(CCHF):
				@mkdir ${CCH_PATH}
				@touch ${CCHF}

clean:
				@rm -rf ${CCH_PATH}
				@rm -f ${CCHF}

fclean:	clean
				@rm -rf ${NAME}
				@echo ${GREEN} " - CLEAN" ${EOC}

re:				fclean
				@make all

.PHONY:			all clean fclean git re