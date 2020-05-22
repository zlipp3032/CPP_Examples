IDIR =include
CC=clang++ -std=c++11
CFLAGS=-I$(IDIR)

ODIR=src/obj
LDIR =lib

LIBS=-lm

_DEPS = examples.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o test.o simple_sim.o medium_sim.o hard_med_sim.o hard_sim.o double_integrator_sim_v02.o form_2ag.o time_stamp.o threading_example.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main_example: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
