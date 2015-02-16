CXX	=	g++
RM	=	rm -f

CPPFLAGS +=	-Wextra -Wall -Werror
CPPFLAGS +=	-std=c++11
CPPFLAGS +=	-I.

LDFLAGS	+=	-static -L/usr/local/lib/ -lboost_unit_test_framework

SRCS	=	$(patsubst %.c,%.o,$(wildcard *.cpp))
OBJS	=	$(SRCS:.cpp=.o)

BIN	=	../bin/
LIB	=	libcorniflex.a
NAME	=	a.out

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CXX) $(OBJS) $(LDFLAGS) -o $(NAME) -l$(subst lib,,$(subst .a,,$(LIB)))

depend:		.depend

.depend:	$(SRCS)
		$(RM) ./.depend
		$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)
		$(RM) ./.depend

re:		fclean all

run:		$(NAME)
		./$(NAME) --build_info=1 --log_level=message --report_level=detailed

debug:		$(NAME)
		valgrind --track-origins=yes ./$(NAME)

include .depend

.PHONY:		all clean fclean re run debug
