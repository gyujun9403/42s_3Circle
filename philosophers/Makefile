TARGET = philo
GCC = gcc
FLAGS = -g3 -fsanitize=address #-Wall -Wextra -Werror
DIR_HEADER = ./header/
DIR_SRCS = ./srcs/
SRCS = main.c utils.c errhandler.c
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