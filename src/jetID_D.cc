#include "fastjet/ClusterSequence.hh"
#include <iostream>
#include <math.h>
#include <time.h>
#include <fstream>
#include <istream>
using namespace fastjet;
using namespace std;

int main () {

vector<int> jet_id;
//vector<string> jet_type;
vector<double> jet_px;
vector<double> jet_py;
vector<double> jet_pz;
vector<double> jet_E;

int id;
//string type;
int status;
double px;
double py;
double pz;
double E;
double m;

int file_n, it = 0;

vector<PseudoJet> particles;
vector<PseudoJet> constituents;

clock_t start, end;

double time;

// Read from Pythia data file 

ifstream infile;
ofstream results0;
ofstream results1;

infile.open("/Users/diogopires/Desktop/jets/Diogo/Events/file_n.txt");
infile >> file_n;
infile.close();

string format(".txt");
string filename("/Users/diogopires/Desktop/jets/Diogo/Events/Ising_test");
string fileresults0("/Users/diogopires/Desktop/jets/Diogo/Results/results0_classical");
string fileresults1("/Users/diogopires/Desktop/jets/Diogo/Results/results1_classical");


for(int f = 30; f < file_n; f++){

  infile.open(filename+to_string(f)+format);// file containing numbers in 3 columns 
    
    if(infile.fail()){ // checks to see if file opened 
      
      cout << "error Jet_ID" << endl; 
      
      return 1; // no point continuing if the file didn't open...
    } 
    
    while(infile >> id >> status >> px >> py >> pz >> E >> m) // reads file to end of *file*, not line
    {   

      jet_id.push_back(id);
      //jet_type.push_back(type);
      jet_px.push_back(px);
      jet_py.push_back(py);
      jet_pz.push_back(pz);
      jet_E.push_back(E);
      
    } 

  infile.close(); 

  //cout << jet_id.size() << endl;
  
  // an event with three particles:   px    py  pz      E

  for(int i = 0; i < jet_id.size(); i++){

    //pythia data set 
    particles.push_back( PseudoJet( jet_px[i], jet_py[i], jet_pz[i], jet_E[i]) );
    particles[i].set_user_index(i); 
  
	}
  
  // choose a jet definition
  
  double R = 0.8;

  JetDefinition jet_def(antikt_algorithm, R);


  start = clock();
  
  // run the clustering, extract the jets
  ClusterSequence cs(particles, jet_def);
  vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());

  end = clock();

  time = double(end-start)/double(CLOCKS_PER_SEC);

  cout << endl;
  cout << "Classical time " << f << ": " << time << " secs" << endl << endl;

  // print out some infos
  cout << "Clustering with " << jet_def.description() << endl;

  // print the jets
  cout << "pt eta phi" << endl;
 
  for (unsigned i = 0; i < jets.size(); i++) {
    
    cout << "jet " << i << ": "<< jets[i].pt() << " " << jets[i].eta() << " " << jets[i].phi()/pi << "π" << endl;
  
    constituents = jets[i].constituents();
    
    for (unsigned j = 0; j < constituents.size(); j++) {
      
      cout << constituents[j].user_index()+1 << " with pt = " << constituents[j].pt() << " is in the house!" << endl;

    }
 
    cout << endl;
  }


  results0.open(fileresults0+to_string(f)+format);
  results1.open(fileresults1+to_string(f)+format);

    for(unsigned j = 0; j < jets[0].constituents().size(); j++){

      results0 << jets[0].constituents()[j].user_index()+1 << "\n";

    }

    for(unsigned j = 0; j < jets[1].constituents().size(); j++){

      results1 << jets[1].constituents()[j].user_index()+1 << "\n";

    }

  results0.close();
  results1.close();

  particles.clear();
  constituents.clear();

  jet_id.clear();
  jet_px.clear();
  jet_py.clear();
  jet_pz.clear();
  jet_E.clear();

  cout << endl;

  }

}

























