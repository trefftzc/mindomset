minDomSet: minDomSet.cpp
	g++ minDomSet.cpp -o minDomSet -O3

minDomSetOMP: minDomSetOMP.cpp
	g++ minDomSetOMP.cpp -o minDomSetOMP -O3 -fopenmp
