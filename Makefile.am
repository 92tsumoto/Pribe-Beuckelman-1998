#INCLUDES = syspara.h

bin_PROGRAMS = PB
PB_CFLAGS = -O2 -axsse4.2 -mkl -parallel -Winline -inline-level=2 -ip -opt-mem-layout-trans=3 -pg -par-report2

PB_LDADD = /home/tsumoto/lib/xhplot.o

PB_SOURCES = ./src/pb.c ./src/ion_current.c \
	./src/exptable.c ./src/mem.c\
	./src/win_out.c ./src/val_constants.c\
	./src/eular.c ./src/input_para.c ./src/system.c\
	./src/eventloop.c ./src/syspara.h

