p255: p255.o list_tree.o dicsup.o stage1_sup.o
	gcc -Wall -o p255 p255.o list_tree.o dicsup.c stage1_sup.o -lm

map5: map5.o list_tree.o dicsup.o stage2_sup.o
	gcc -Wall -o map5 map5.o list_tree.o dicsup.o stage2_sup.o -lm

stage1_sup.o: stage1_sup.c stage1_sup.h
	gcc -Wall -c stage1_sup.c -lm

dicsup.o: dicsup.c dicsup.h
	gcc -Wall -c dicsup.c -lm

list_tree.o: list_tree.c list_tree.h
	gcc -Wall -c list_tree.c -lm

p255.o: p255.c list_tree.h dicsup.h stage1_sup.h
	gcc -Wall -c p255.c -lm

stage2_sup.o: stage2_sup.c stage2_sup.h
	gcc -Wall -c stage2_sup.c -lm

map5.o: map5.c list_tree.h dicsup.h stage2_sup.h
	gcc -Wall -c map5.c -lm