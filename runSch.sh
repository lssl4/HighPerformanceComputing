#PBS -l nodes=20:ppn=5
#PBS -m abe
#PBS -M 20753794@student.uwa.edu.au
source /etc/bash.bashrc
mpirun mainfileOMPAndMPI data.txt keys.txt 4400 500 0.000001
