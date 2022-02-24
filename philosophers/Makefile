# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/22 12:49:44 by gyeon             #+#    #+#              #
#    Updated: 2022/02/24 19:50:24 by gyeon            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET = philo
TARGET_BONUS = philo_bonus
GCC = gcc
FLAGS = -g #-Wall -Wextra -Werror #-g3 -fsanitize=address  
DIR_HEADER = ./header/
DIR_SRCS = ./srcs/
DIR_SRCS_BONUS = ./srcs_bonus/
SRCS = main.c utils.c errhandler.c actions.c time.c parsing.c pthreads.c mutexs.c set_philos.c mutex_print.c
SRCS_BONUS = main.c utils.c errhandler.c actions.c time.c parsing.c routine.c syscall.c set_philo.c sem_print.c
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all : $(TARGET) $(TARGET_BONUS)
man : $(TARGET)
bonus : $(TARGET_BONUS)
$(TARGET) : $(addprefix $(DIR_SRCS), $(OBJS))
	$(GCC) $(FLAGS) -o $@ $^
$(TARGET_BONUS) : $(addprefix $(DIR_SRCS_BONUS), $(OBJS_BONUS))
	$(GCC) $(FLAGS) -o $@ $^
%.o : %.c
	$(GCC) $(FLAGS) -c $< -o $@ -I $(DIR_HEADER)
clean :
	rm -rf $(addprefix $(DIR_SRCS), $(OBJS)) $(addprefix $(DIR_SRCS_BONUS), $(OBJS_BONUS))
fclean : clean
	rm -rf $(TARGET) $(TARGET_BONUS)
re : fclean all
.PHONY : all clean fclean