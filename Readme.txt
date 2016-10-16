**************************************************************************************

Steps to install pbc library:

**************************************************************************************

1. Unzip the tar.gz file
	 tar -xvzf pbc-0.5.14.tar.gz
2. Enter the newly created directory
	 cd pbc-0.5.14/
3. Install lex and bison unless already installed on the system (use yum if apt-get missing):
	sudo apt-get upgrade
	sudo apt-get install flex bison
4. ./configure
5. make
6. make install
7. sudo ldconfig /usr/local/lib
8. If gmp is not present please execute:
	sudo apt-get install libgmp3-dev

**************************************************************************************

Steps to compile the codes

**************************************************************************************
gcc KAC-1.c -L. -lpbc -lgmp -o KAC-1

Similarly for others
**************************************************************************************






