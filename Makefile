# Copyright (c) 2016,2023 Louis P. Santillan <lpsantil@gmail.com>
# All rights reserved.
# See LICENSE for licensing details.

#SHELL := /bin/bash
SHELL := /opt/homebrew/bin/bash

DESTDIR ?= /usr/local

######################################################################
# Core count
CORES ?= 1

# Basic feature detection
OS = $(shell uname)
ARCH ?= $(shell uname -m)

######################################################################

#CFLAGS ?= -Os -Wall -std=gnu99 -pedantic -Wno-dollar-in-identifier-extension
CFLAGS ?= -Os -Wall -std=gnu11 -pedantic -Wno-dollar-in-identifier-extension -fms-extensions
LDFLAGS ?=

DDIR = docs
DSRC =
SRC = $(wildcard src/lib/*.c)
OBJ = $(SRC:.c=.o)
SDEPS = $(SRC:.c=.d)
HDR = oop0/oop0.h
IDIR = include
INC = $(IDIR)/$(HDR)
EDIR = .
EXE =
LNK = oop0
LDIR = lib
LSRC = $(wildcard src/lib/*.c)
LOBJ = $(LSRC:.c=.o)
LSDEPS = $(LSRC:.c=.d)
LIB = $(LDIR)/lib$(LNK).a
TDIR = t
TSRC = $(wildcard t/*.c)
TOBJ = $(TSRC:.c=.o)
TSDEPS = $(TSRC:.c=.d)
TEXE = $(TOBJ:.o=.exe)

######################################################################
######################## DO NOT MODIFY BELOW #########################
######################################################################

.PHONY: all test runtest clean install uninstall showconfig gstat
.PHONY: gpush tarball

%.o: %.c $(INC) Makefile
	$(CC) $(CFLAGS) -MMD -MP -I$(IDIR) -c $< -o $@

t/%.exe: t/%.o $(LIB) Makefile
	$(LD) -L$(LDIR) -l$(LNK) $(LDFLAGS) $< -o $@

all: $(LIB)

$(LIB): $(LOBJ)
	$(AR) -rs $@ $^

$(EXE): $(OBJ)
	$(LD) $^ $(LDFLAGS) -o $(EDIR)/$@

test: $(LIB) $(TEXE) Makefile

runtest: $(TEXE)
	for T in $^ ; do $(TAP) $$T ; done

clean:
	rm -fv $(OBJ) $(EXE) $(LOBJ) $(LIB) $(TOBJ) $(TEXE) $(SYSINC) *.tmp $(SDEPS) $(LSDEPS) $(TSDEPS)

install: $(INC) $(LIB)
#	mkdir -p $(DESTDIR)/include/oop0 $(DESTDIR)/lib
#	rm -f .footprint
#	@for T in $(INC) $(LIB); \
#	do ( \
#		echo $(DESTDIR)/$$T >> .footprint; \
#		cp -v --parents $$T $(DESTDIR) \
#	); done

uninstall: .footprint
	@for T in `cat .footprint`; do rm -v $$T; done

-include $(SDEPS) $(LSDEPS) $(TSDEPS)

showconfig: p-OS p-ARCH p-DESTDIR p-CC p-LD p-AR p-CFLAGS p-LDFLAGS p-DDIR p-DSRC p-SRC p-OBJ p-HDR p-IDIR p-INC p-EDIR p-EXE p-TSRC p-TOBJ p-TEXE

gstat:
	git status

gpush:
	git commit
	git push

tarball:
	cd ../. && tar jcvf oop0.$(shell date +%Y%m%d%H%M%S).tar.bz2 oop0

define newline # a literal \n


endef
# Makefile debugging trick:
# call print-VARIABLE to see the runtime value of any variable
# (hardened a bit against some special characters appearing in the output)
p-%:
	@echo '$*=$(subst ','\'',$(subst $(newline),\n,$($*)))'
.PHONY: p-*

help: ## This help target
	echo $(SHELL) - $(MAKEFILE_LIST)
	@RE='^[a-zA-Z0-9 ._+-]*:[a-zA-Z0-9 ._+-]*##' ; while read line ; do [[ "$$line" =~ $$RE ]] && echo "$$line" ; done <Makefile ; RE=''
