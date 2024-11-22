CC = cc
CFLAGS = -c -Wall -Wextra -g

OBJDIR = build
OBJ = $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(wildcard *.c)))
all: $(OBJDIR) prog

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

prog: $(OBJ)
	$(CC) -o $@ $^

clean:
	rm -Rf $(OBJDIR)
	rm -rf prog
