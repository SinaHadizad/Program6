#Sina Hadizad
#srh160630@cs1.utdallas.edu
#CS3377.002

CXX = g++
CXXFLAGS =
CPPFLAGS = -Wall -g -I /scratch/perkins/include
LDFLAGS = -L /scratch/perkins/lib
LDLIBS = -lcdk -lcurses

EXECFILE = 6

OBJS = cdkMatrix.o

all: $(EXECFILE)

clean:
	rm -f $(EXECFILE) *.P *~ \#* *.o

$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)

backup:
	@make clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename "`pwd`"))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME) 2> /dev/null
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!
