# The parameters
cflags =
libs =
device =
builddir =
sourcedir =
outdir =

EXEC = a.out
SRCDIR = $(shell pwd)
BLDDIR = $(SRCDIR)
OBJDIR = $(BLDDIR)/obj
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

INCLUDES = -I.
LDFLAGS = -lhiredis -lglib-2.0

_PLATFORM = $(shell uname -s)

ifeq ($(_PLATFORM), Linux)
  PLAT_INCLUDES =
  PLAT_LDFLAGS =
else
 ifeq ($(_PLATFORM), Darwin)

  CC = clang
  PLAT_INCLUDES = -I/usr/local/include/ \
				  -I/usr/local/include/glib-2.0 \
				  -I/usr/local/lib/glib-2.0/include
  PLAT_LDFLAGS = -L/usr/local/lib
 else
  $(error "Unknown platform, need to be supported.")
 endif
endif

CFLAGS = -Wall -g $(cflags) $(INCLUDES) $(PLAT_INCLUDES)
LIBS = $(libs) $(LDFLAGS) $(PLAT_LDFLAGS)

all: $(EXEC)

$(EXEC): $(OBJS)
	@echo "  [LD]    $(notdir $@)"
	@$(CC) -o $@ $(LIBS) $^

$(OBJS):$(OBJDIR)/%.o:$(SRCDIR)/%.c
	@install -d $(OBJDIR)
	@echo "  [CC]    $(notdir $@)"
	@$(CC) -c -o $@ $(CFLAGS) $<


clean:
	-rm -f $(OBJS) $(EXEC)
