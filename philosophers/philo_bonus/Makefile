# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/22 12:49:44 by gyeon             #+#    #+#              #
#    Updated: 2022/02/28 16:39:24 by gyeon            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET_BONUS = philo_bonus
GCC = gcc
FLAGS = -Wall -Wextra -Werror
DIR_HEADER = ./header/
DIR_SRCS_BONUS = ./srcs_bonus/
SRCS_BONUS = main_bonus.c utils_bonus.c errhandler_bonus.c \
	actions_bonus.c time_bonus.c parsing_bonus.c routine_bonus.c \
	syscall_bonus.c set_philo_bonus.c sem_print_bonus.c
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all : $(TARGET_BONUS)
$(TARGET_BONUS) : $(addprefix $(DIR_SRCS_BONUS), $(OBJS_BONUS))
	$(GCC) $(FLAGS) -o $@ $^
%.o : %.c
	$(GCC) $(FLAGS) -c $< -o $@ -I $(DIR_HEADER)
clean :
	rm -rf $(addprefix $(DIR_SRCS_BONUS), $(OBJS_BONUS))
fclean : clean
	rm -rf $(TARGET_BONUS)
re : fclean all
.PHONY : all clean fclean