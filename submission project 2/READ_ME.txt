This project was done by Tzi Siong Leong (20753794) and Jason Chao (21397806)

The collision matrix project file is mainfileOMPAndMPI.cpp with finalNeighbors.cpp and type.h as the accompanying files.

To compile and run our code use the following commmand lines

mpic++ -fopenmp -std=c++11 mainfileOMPAndMPI.cpp -o mainfileOMPAndMPI

Our runSch script used for qsub is:

#PBS -l nodes=20:ppn=5
source /etc/bash.bashrc
mpirun mainfileOMPAndMPI data.txt keys.txt 4400 500 0.000001

where mainfileOMPAndMPI is the name of our executable which requires the following command line arguments:
<executable> <data file> <keys file> <data file rows> <data file columns> <dia distance>

