LIBS = 
CFLAGS = -Wall -fPIC --std=gnu18 $(LIBS)
INC = 
CC = gcc
PROJ = ADCDevice
all: $(PROJ)

debug: CFLAGS += -DDEBUG -g
debug: DEBUG = debug
debug: $(PROJ)

$(PROJ):
	$(CC) $(CFLAGS) -c $(PROJ).c -o $(PROJ).o
	$(CC) -shared $(CFLAGS) -o lib$(PROJ).so $(PROJ).o

install:
	@echo -n "Initializing installation directories ... "
	@/bin/mkdir -p   /usr/include  /usr/lib && echo -n ".."  || exit
	@/bin/chmod 0755 /usr/include  /usr/lib && echo -n ".. " || exit
	@echo "done"
	@/bin/cp    -v   $(PROJ).h     /usr/include/
	@/bin/cp    -v   lib$(PROJ).so /usr/lib/
	@/usr/sbin/ldconfig
	@/bin/chmod 0644 /usr/include/$(PROJ).h
	@/bin/chmod 0644 /usr/lib/lib$(PROJ).so
	@echo "INSTALLATION COMPLETE"

clean:
	@rm -vrf .*.sw[op] *.o lib$(PROJ).so *.save* *~ core
