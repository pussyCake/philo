
NAME = philo

FLAG = -Wall -Wextra -Werror -pthread

S_DIR = srcs

O_DIR = obj

INCLUDE = -I./include 

SRC =	main.c\
		live.c\
		utils_lib.c\
		utils_phil.c\
		error.c\
		init.c

SRCS = $(addprefix $(S_DIR)/,$(SRC))

OBJS = $(addprefix $(O_DIR)/,$(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) 
	gcc $(OBJS) $(FLAG) $(INCLUDE)  -o $(NAME)

$(O_DIR)/%.o: $(S_DIR)/%.c
	mkdir -p obj
	gcc $(FLAG) $(INCLUDE) -o $@ -c $< 

clean:
	rm -f $(OBJS)
	rm -rf $(O_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all

.PHONY:  all clean fclean re
