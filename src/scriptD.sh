#!/bin/bash

######### RUN FROM 'Desktop/jets/Diogo' FOLDER	

cd 

cd Desktop/pythia8244/examples

make maindiogo

./maindiogo

cd

cd Desktop/jets/Diogo


####### Running Fastjet to cluster jets from pythia dataset

g++ jetID_D.cc -o jets `fastjet-install/bin/fastjet-config --cxxflags --libs --plugins`
./jets



####### Writing J-Matrix to .txt file

g++ Ising_Couplings.cpp -o j
./j




####### Connecting and running problem on D-Wave machine


python qc_ising.py






####### Getting the results (quantum vs classical)

g++ AnalysisD.cpp -o analysis
./analysis


####### Warning to mobile phone
osascript -e 'tell application "Messages" to send "Finished Running" to buddy "Diogo Pires"'
