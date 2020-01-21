NAME_ASM = asm
LIBFT_A = ./lib/libft/libft.a
FLAGS = -Wall -Wextra -Werror
COMP = gcc -c -o
ASM_H = -I ./includes/

OBJ_DIR =	./obj/

SRC_DIR =	./source/asm/

C_FILE =	main.c

C_FIND =		$(addprefix $(SRC_P_DIR), $(C_FILE))

O_FILE =		$(C_FILE:%.c=%.o)

OBJ =		$(addprefix $(OBJ_DIR), $(O_FILE))

all: $(NAME_ASM)

$(NAME_ASM): $(OBJ_DIR) $(OBJ)
	@make -C ./lib/libft
	@gcc $(LIBFT_A) $(OBJ) -o $(NAME_ASM)
	@echo $(NAME_ASM) create

$(OBJ_DIR):
			@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
			@echo Create: $(@:obj/%=%)
			@gcc $(FLAGS) -c $< -o $@

clean:
		@rm -rf obj
		@make -C lib/libft clean

fclean: clean
		@rm -rf ./$(NAME_ASM)
		@make -C lib/libft fclean

re: fclean all

.PHONY: all clean flcean re