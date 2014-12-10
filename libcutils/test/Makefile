# The parameters
cflags =
libs =
builddir =
sourcedir =
outdir =

SRCDIR = $(shell pwd)
BLDDIR = $(SRCDIR)
OBJDIR = $(BLDDIR)/obj
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

TEST_CASES = $(patsubst $(SRCDIR)/%.c, %.out, $(SRCS))

INCLUDES =
LDFLAGS =

_PLATFORM = $(shell uname -s)

ifeq ($(_PLATFORM), Linux)
  PLAT_INCLUDES =
  PLAT_LDFLAGS =
else
 ifeq ($(_PLATFORM), Darwin)
  CC = clang
  PLAT_INCLUDES =
  PLAT_LDFLAGS =
 else
  $(error "Unknown platform, need to be supported.")
 endif
endif

CFLAGS = -Wall -fPIC $(cflags) $(INCLUDES) $(PLAT_INCLUDES)
LIBS = $(libs) $(LDFLAGS) $(PLAT_LDFLAGS) -lcutils

all: $(TEST_CASES)

$(OBJS):$(OBJDIR)/%.o:$(SRCDIR)/%.c
	@install -d $(OBJDIR)
	@echo "  [CC]    $(notdir $@)"
	@$(CC) -c -o $@ $(CFLAGS) $<

clean:
	-rm -f $(OBJS) $(TEST_CASES)

$(TEST_CASES): %.out: $(OBJDIR)/%.o
	@echo "  [LD]    $@"
	@$(CC) -o $@ $^ $(LIBS)


