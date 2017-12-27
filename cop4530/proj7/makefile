# makefile for Graph Project
# Blake Kershaw
# COP4530
# April 10th, 2017

HOME   = /home/courses/cop4530p/LIB
CPP    = $(HOME)/cpp
TCPP   = $(HOME)/tcpp
AREA51 = $(HOME)/area51
TESTS  = $(HOME)/tests

#CC     = g++ -std=c++11 -Wall -Wextra -I. -I$(CPP) -I$(TCPP)
CC     = clang++ -std=c++11 -I. -I$(CPP) -I$(TCPP)

# -Weverything -Wno-old-style-cast

all: fgraph.x fbfs_ug.x fbfs_dg.x fdfs_ug.x fdfs_dg.x rangraph.x agraph.x

fgraph.x: fgraph.o
	$(CC) -ofgraph.x fgraph.cpp  

fgraph.o: fgraph.cpp $(TCPP)/ansicodes.h $(TCPP)/graph_util.h $(TCPP)/topsort.h	$(TCPP)/queue.h $(TCPP)/list.h $(TCPP)/vector.h graph.h
	$(CC) -c fgraph.cpp

fdfs_dg.x: fdfsurvey_dg.cpp graph.h dfsurvey.h
	$(CC) -ofdfs_dg.x fdfsurvey_dg.cpp

fdfs_ug.x: fdfsurvey_ug.cpp graph.h dfsurvey.h
	$(CC) -ofdfs_ug.x fdfsurvey_ug.cpp

fbfs_ug.x: fbfsurvey_ug.cpp graph.h bfsurvey.h
	$(CC) -ofbfs_ug.x fbfsurvey_ug.cpp

fbfs_dg.x: fbfsurvey_dg.cpp graph.h bfsurvey.h 
	$(CC) -ofbfs_dg.x fbfsurvey_dg.cpp

rangraph.x: $(AREA51)/rangraph_i.x
	cp $(AREA51)/rangraph_i.x rangraph.x
	chmod 700 rangraph.x

agraph.x: $(AREA51)/agraph_i.x
	cp $(AREA51)/agraph_i.x agraph.x
	chmod 700 agraph.x
