# The parameters
cflags =
libs =
device =
builddir =
sourcedir =
outdir =

LIBEXEC = libcutils
SUFFIX = .so
PERIOD = .0
MINOR = .0
RELEASE = .1
REALLIB = $(LIBEXEC)$(SUFFIX)$(PERIOD)$(MINOR)$(RELEASE)
SONAME = $(LIBEXEC)$(SUFFIX)$(PERIOD)
LINKNAME = $(LIBEXEC)$(SUFFIX)
STATIC_LIB = $(LIBEXEC).a

SRCDIR = $(shell pwd)
BLDDIR = $(SRCDIR)
OBJDIR = $(BLDDIR)/obj
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

INCLUDES =
LDFLAGS =

_PLATFORM = $(shell uname -s)

ifeq ($(_PLATFORM), Linux)
  PLAT_INCLUDES =
  PLAT_LDFLAGS = -shared -Wl,-soname,$(SONAME)
else
 ifeq ($(_PLATFORM), Darwin)
  REALLIB = $(LIBEXEC)$(PERIOD)$(MINOR)$(RELEASE).dylib
  SONAME = $(LIBEXEC)$(PERIOD).dylib
  LINKNAME = $(LIBEXEC).dylib

  CC = clang
  PLAT_INCLUDES =
  PLAT_LDFLAGS = -dynamiclib -Wl,-install_name,$(BLDDIR)/$(SONAME)
 else
  $(error "Unknown platform, need to be supported.")
 endif
endif

CFLAGS = -Wall -fPIC $(cflags) $(INCLUDES) $(PLAT_INCLUDES)
LIBS = $(libs) $(LDFLAGS) $(PLAT_LDFLAGS)

all: $(REALLIB) static-lib test-case

$(STATIC_LIB): $(OBJS)
	@echo "  [AR]    $(notdir $@)"
	@ar rcs $@ $^

$(REALLIB): $(OBJS)
	@echo "  [LD]    $(notdir $@)"
	@$(CC) -o $@ $(LIBS) $^
	@-ln -s $@ $(SONAME)
	@-ln -s $@ $(LINKNAME)

$(OBJS):$(OBJDIR)/%.o:$(SRCDIR)/%.c
	@install -d $(OBJDIR)
	@echo "  [CC]    $(notdir $@)"
	@$(CC) -c -o $@ $(CFLAGS) $<

static-lib: $(STATIC_LIB)

test-case:
	@make -C $(SRCDIR)/test cflags=-I$(SRCDIR) libs="-L$(BLDDIR) \
		-Wl,-rpath,$(BLDDIR)"

clean:
	-rm -f $(OBJS) $(REALLIB) $(SONAME) $(LINKNAME) $(STATIC_LIB)
	@make -C $(SRCDIR)/test clean
