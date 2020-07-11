OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Especie.o  Cjt_Especies.o Cjt_Clusters.o Cluster.o
	g++ -o program.exe *.o

Especie.o: Especie.cc Especie.hh
	g++ -c Especie.cc $(OPCIONS)

Cjt_Especies.o: Especie.o  Cjt_Especies.cc  Cjt_Especies.hh
	g++ -c  Cjt_Especies.cc $(OPCIONS)
	
Cjt_Clusters.o: Cjt_Especies.o  Cjt_Clusters.cc  Cjt_Clusters.hh BinTree.hh
	g++ -c  Cjt_Clusters.cc $(OPCIONS)

Cluster.o:  Cluster.cc  Cluster.hh BinTree.hh
	g++ -c  Cluster.cc $(OPCIONS)

program.o: program.cc Cjt_Especies.hh Cjt_Clusters.hh
	g++ -c program.cc $(OPCIONS)

clean:
	rm -f *.o
	rm -f *.exe
