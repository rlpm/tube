# Stonecutters CS351 S03

TOP=..
include $(TOP)/Makefile.vars$(MKSUFFIX)
include Makefile.vars$(MKSUFFIX)

SRC=$(OFILES:.o=.C)

all:	$(COMMONLIBDEP)
	@echo "Made in common"

$(COMMONLIBDEP):	$(OFILES) $(ALLDEP)
	ar crv $(COMMONLIBDEP) $(OFILES)
	ranlib $(COMMONLIBDEP)

clean:
	rm -f *.o core *~ a.out

distclean: clean
	rm -f *.a
	rm -f depend.make

%.o:	%.C %.h
	$(CXX) $(CFLAGS) $*.C -o $@

# Dave has a little Version class to expose the version inside the code
Version.o:	Version.C Version.h $(ALLDEP)
	$(CXX) $(CFLAGS) -DTUBEMAJOR=$(TUBEMAJOR) -DTUBEMINOR=$(TUBEMINOR) -DTUBERELEASE=$(TUBERELEASE) $*.C -o $@

# make the dependency lists
depend.make:  Makefile $(SRC) $(SRC:%.C=%.h)
	$(CXX) -E -MM $(CFLAGS) $(SRC) > depend.make
depend: depend.make

# DO NOT DELETE THE FOLLOWING LINE
include depend.make
