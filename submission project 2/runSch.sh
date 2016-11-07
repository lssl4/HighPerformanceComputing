#PBS -l nodes=20:ppn=5
source /etc/bash.bashrc
mpirun mainfileOMPAndMPI data.txt keys.txt 4400 500 0.000001
