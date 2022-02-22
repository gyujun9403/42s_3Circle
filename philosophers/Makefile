# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/22 12:49:44 by gyeon             #+#    #+#              #
#    Updated: 2022/02/22 12:49:57 by gyeon            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET = philo
GCC = gcc
FLAGS = -g3 -fsanitize=address -Wall -Wextra -Werror
DIR_HEADER = ./header/
DIR_SRCS = ./srcs/
SRCS = main.c utils.c errhandler.c actions.c time.c parsing.c pthreads.c mutexs.c set_philos.c
OBJS = $(SRCS:.c=.o)

all : $(TARGET)
$(TARGET) : $(addprefix $(DIR_SRCS), $(OBJS))
	$(GCC) $(FLAGS) -o $@ $^
%.o : %.c
	$(GCC) $(FLAGS) -c $< -o $@ -I $(DIR_HEADER)
clean :
	rm -rf $(addprefix $(DIR_SRCS), $(OBJS))
fclean : clean
	rm -rf $(TARGET)
re : fclean all
.PHONY : all clean fclean