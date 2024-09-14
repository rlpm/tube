# Stonecutters CS351 S03

TOP=..
include $(TOP)/Makefile.vars$(MKSUFFIX)
include Makefile.vars$(MKSUFFIX)

SRC=$(OFILES:.o=.C)

all:	$(TOP)/$(CLIENTNAME)
	@echo "Made in Client"

$(TOP)/$(CLIENTNAME):	$(OFILES) $(COMMONLIBDEP)
	$(CXX) $(OFILES) -o $(TOP)/$(CLIENTNAME) $(LFLAGS) 

clean:	
	rm -f *.o core *~ a.out

distclean: clean
	rm -f $(TOP)/$(CLIENTNAME)
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
