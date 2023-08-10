NAME = minishell

SRC = $(NAME) cmd_echo cmd_cd cmd_env cmd_exit cmd_export cmd_pwd cmd_unset init_vars \
	free_vars utils utils2 work_command cmd_setenv check_cmd_line check_quotes \
	tokenize token_utils token_utils2 print_var replace_env_var cmd_exec adm_signal \
	actualize_env concat_cmd get_cmd ft_leninstr adm_redirections ft_str_arr_add \
	ft_str_arr_rem adm_file_redir check_delimiter ft_split_instr ft_strrmstr
	
#añadir nombres de ficheros.c  aqui

INC = $(NAME) colors #añadir nombres de ficheros.h  aqui

DIR_SRC = ./src/

INCDIR = ./inc/

DIR_OBJ_DST = ./obj_dst/

SRCS = $(addprefix $(DIR_SRC),$(addsuffix .c,$(SRC)))
SRCS = $(addprefix $(DIR_SRC),$(addsuffix .c,$(SRC)))
OBJS = $(addprefix $(DIR_OBJ_DST),$(addsuffix .o,$(SRC)))
DSTS = $(addprefix $(DIR_OBJ_DST),$(addsuffix .d,$(SRC)))
INCLUDE:= $(addprefix $(INCDIR),$(addsuffix .h, $(INC)))

#NEXTLINE LIBRARY
DIR_NEXTLINE = ./Nextline/
NEXTLINE = $(addprefix $(DIR_NEXTLINE),get_next_line.a)

#FT_PRINTF LIBRARY
DIR_PRINTF = ./ft_printf/
FT_PRINTF = $(addprefix $(DIR_PRINTF),libftprintf.a)

CC:= gcc

FLAGS:= -Werror -Wextra -Wall -O2 -g $(SANIT1)

#-fsanitize=datarace -fsanitize=address
RM := rm -rfd

all: $(FT_PRINTF) $(NEXTLINE) $(NAME)


all_lk:SANIT1 = -fsanitize=address
all_lk:SANIT2 = -static-libsan
all_lk: all


linux_lk: SANIT1 = -fsanitize=address
linux_lk: SANIT2 = -static-libasan
linux_lk: all

-include $(DSTS)

$(NAME): $(OBJS) Makefile
	$(CC) $(FLAGS) $(SANIT1) -v $(OBJS) -o $(NAME) $(FT_PRINTF) $(NEXTLINE) $(LIBFT) -lreadline 

#-static-libsan 
$(DIR_OBJ_DST)%.o: $(DIR_SRC)%.c $(DIR_OBJ_DST)%.d
	@mkdir -p $(DIR_OBJ_DST)
	@printf "\rCompiling: $(notdir $<).\r"
	@$(CC) $(FLAGS) -I$(INCDIR) $(SANIT2) -c $(DIR_SRC)$*.c -o $(DIR_OBJ_DST)$*.o 

$(DIR_OBJ_DST)%.d: $(DIR_SRC)%.c $(INCLUDE)
	@mkdir -p $(DIR_OBJ_DST)
	@$(CC) $(FLAGS) -I$(INCDIR) -MM -c $(DIR_SRC)$*.c -o $(DIR_OBJ_DST)$*.d 

$(FT_PRINTF):
	make -C$(DIR_PRINTF)

$(NEXTLINE):
	make -C$(DIR_NEXTLINE)

clean:
	@$(RM) $(DIR_OBJ_DST)
	make -C$(DIR_NEXTLINE) clean
	make -C$(DIR_PRINTF) clean

fclean: clean
	@$(RM) $(NAME)
	make -C$(DIR_NEXTLINE) fclean
	make -C$(DIR_PRINTF) fclean

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

.PHONY: all re clean fclean print libft $(FT_PRINTF) $(NEXTLINE) linux_lk all_lk
