NAME = minishell

SRC = $(NAME) cmd_echo cmd_cd cmd_env cmd_exit cmd_export cmd_pwd cmd_unset init_vars \
	free_vars utils work_command split_inst cmd_setenv check_cmd_line check_quotes \
	tokenize token_utils print_var replace_env_var cmd_exec adm_signal actualize_env \
	concat_cmd #añadir nombres de ficheros.c  aqui

INC = $(NAME) #añadir nombres de ficheros.h  aqui

DIR_SRC = ./src/

INCDIR = ./inc/

DIR_OBJ_DST = ./obj_dst/

SRCS = $(addprefix $(DIR_SRC),$(addsuffix .c,$(SRC)))
SRCS = $(addprefix $(DIR_SRC),$(addsuffix .c,$(SRC)))
OBJS = $(addprefix $(DIR_OBJ_DST),$(addsuffix .o,$(SRC)))
DSTS = $(addprefix $(DIR_OBJ_DST),$(addsuffix .d,$(SRC)))
INCLUDE:= $(addprefix $(INCDIR),$(addsuffix .h, $(INC)))

#LIBFT LIBRARY
DIR_LIBFT = ./libft/
LIBFT = $(addprefix $(DIR_LIBFT),libft.a)

CC:= gcc

FLAGS:= -Werror -Wextra -Wall -O2 -g -fsanitize=address

#-fsanitize=datarace -fsanitize=address
RM := rm -rfd

SANIT = -libsan

all: $(LIBFT) $(NAME)

linux: SANIT = -libasan
linux:  all

-include $(DSTS)


$(NAME): $(OBJS) Makefile
	$(CC) $(FLAGS) -v $(OBJS) -o $(NAME) $(LIBFT) -lreadline 

#-static-libsan 
$(DIR_OBJ_DST)%.o: $(DIR_SRC)%.c $(DIR_OBJ_DST)%.d
	@mkdir -p $(DIR_OBJ_DST)
	@printf "\rCompiling: $(notdir $<).\r"
	@$(CC) $(FLAGS) -I$(INCDIR) -static$(SANIT) -c $(DIR_SRC)$*.c -o $(DIR_OBJ_DST)$*.o 

$(DIR_OBJ_DST)%.d: $(DIR_SRC)%.c $(INCLUDE)
	@mkdir -p $(DIR_OBJ_DST)
	@$(CC) $(FLAGS) -I$(INCDIR) -MM -c $(DIR_SRC)$*.c -o $(DIR_OBJ_DST)$*.d 

$(LIBFT):
	make -C$(DIR_LIBFT)

clean:
	@$(RM) $(DIR_OBJ_DST)
	make -C$(DIR_LIBFT) clean

fclean: clean
	@$(RM) $(NAME)
	make -C$(DIR_LIBFT) fclean

re: fclean all

linux_re:   fclean linux

print:
	@echo INCLUDE: $(INCLUDE)
	@echo NAME: $(NAME)
	@echo SRC: $(SRCS)
	@echo OBJS: $(OBJS)
	@echo DSTS: $(DSTS)
	@echo DIR_OBJ_DST: $(DIR_OBJ_DST)
	@echo INCDIR: $(INCDIR)
	@echo INCLUDE: $(INCLUDE)
	@echo DIRLIBFT: $(DIR_LIBFT)
	@echo LIBFT: $(LIBFT)

.PHONY: all re clean fclean print libft $(LIBFT) linux linux_re
