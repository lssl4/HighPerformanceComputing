#PBS -l nodes=20:ppn=5
#PBS -m abe
#PBS -M 20753794@student.uwa.edu.au
source /etc/bash.bashrc
mpirun /home/uniwa/students4/students/20753794/linux/CITS3402/mainfile2OMP data.txt keys.txt 4400 500 0.000001
