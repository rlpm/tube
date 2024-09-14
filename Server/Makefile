# Stonecutters CS351 S03
# $Id: Makefile,v 1.6 2003/05/08 23:52:41 rlpm Exp $

TOP=..
include $(TOP)/Makefile.vars$(MKSUFFIX)
include Makefile.vars$(MKSUFFIX)

SRC=$(OFILES:.o=.C)

all:	$(TOP)/$(SERVERNAME)
	@echo "Made in Server"

$(TOP)/$(SERVERNAME):	$(OFILES) $(COMMONLIBDEP)
	$(CXX) $(OFILES) -o $(TOP)/$(SERVERNAME) $(LFLAGS) 

clean:	
	rm -f *.o core *~ a.out

distclean: clean
	rm -f $(TOP)/$(SERVERNAME)
	rm -f depend.make

%.o:	%.C %.h
	$(CXX) $(CFLAGS) $*.C -o $@

$(COMMONLIBDEP): FORCE
	@cd $(COMMONDIR); \
	make

.PHONY:	FORCE

# make the dependency lists
depend.make:  Makefile $(SRC) $(SRC:%.C=%.h)
	$(CXX) -E -MM $(CFLAGS) $(SRC) > depend.make
depend: depend.make

# DO NOT DELETE THE FOLLOWING LINE
include depend.make
