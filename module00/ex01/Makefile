NORMAL = "\x1B[0m"
RED = "\x1B[31m"
GREEN = "\x1B[32m"
YELLOW = "\x1B[33m"
BLUE = "\x1B[34m"
MAGENTA = "\x1B[35m"
CYAN = "\x1B[36m"
WHITE = "\x1B[37m"
BOLD = "\e[1m"
LIGHT = "\e[2m"
ITALIC = "\e[3m"
ULINE = "\e[4m"

START = @printf $(CYAN)$(BOLD)"Divide & Conquer\n--------------------\n"$(NORMAL)
END = @printf $(CYAN)$(BOLD)"COMPILATION [OK]\n--------------------\n"$(NORMAL)

NAME	=	Graph
OS		=	$(shell uname)

# directories
SRCDIR		=	./src
INCDIR		=	./includes
OBJDIR		=	./obj

# src / obj files
SRC		=	main.cpp\
			Vector2.cpp\
			Graph.cpp\


OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.cpp=.o))
SDEP	= $(addprefix $(OBJDIR)/,$(SRC:.cpp=.d))

# ensemble des fichiers de dependance
DEP= $(SDEP)


# compiler
CC		= c++ $(CFLAGS)
CFLAGS	= #-Wall -Wextra -Werror -g3 -std=c++98

all:	obj $(NAME)
# 		$(START)
# 		$(END)


obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:	$(SRCDIR)/%.cpp
	$(CC) -I $(INCDIR) -o $@ -c $<


$(NAME): $(OBJ)
	$(CC) $(OBJ) -lm -o $(NAME)

clean:
	rm -rf $(OBJDIR) $(DEP)

fclean: clean
	rm -rf $(NAME)

re: fclean
	make all

-include $(DEP)