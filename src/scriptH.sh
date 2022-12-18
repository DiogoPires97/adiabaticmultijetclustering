#!/bin/bash

######### RUN FROM 'Desktop/jets/Diogo' FOLDER	



####### Running Fastjet to cluster jets from pythia dataset

#g++ jetID_D.cc -o jets `fastjet-install/bin/fastjet-config --cxxflags --libs --plugins`
#./jets



####### Writing Q-Matrix to .txt file

g++ Q-Matrix_harrow.cpp -o qmatrix
./qmatrix




####### Connecting and running problem on D-Wave machine


python qc_harrow.py




####### Getting the results (quantum vs harrow)

g++ AnalysisH.cpp -o analysish
./analysish


####### Warning to mobile phone
osascript -e 'tell application "Messages" to send "Finished Running" to buddy "Diogo Pires"'
