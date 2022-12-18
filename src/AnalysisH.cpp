#include <iostream>
#include <math.h>
#include <fstream>
#include <istream>
#include <vector>

using namespace std;

int main() {


ifstream infile;

string format(".txt");

int file_n;

infile.open("/Users/diogopires/Desktop/jets/Diogo/Events/file_n.txt");
infile >> file_n;
infile.close();

/////

int jet0, jet1, parh, jparh;

vector<int> Jet0;
vector<int> Jet1;

string filename0("/Users/diogopires/Desktop/jets/Diogo/Results/results_harrow");

/////

int partition_bool, particle_id;

vector<int> partition0;
vector<int> partition1;

string filequantum("/Users/diogopires/Desktop/jets/Diogo/Results/results_clustering");

/////

int n_successes0 = 0, n_successes1 = 0, n_successes00 = 0, n_successes11 = 0;
double success0, success1, success00, success11;

vector<int>::iterator ans0;
vector<int>::iterator ans1;

vector<int>::iterator ans00;
vector<int>::iterator ans11;

/////

int eff = 0;
vector<int> Eff;


for(int f = 0; f < file_n; f++){

  
  ///////////////////////////////////////////////////////////////
  //Load Harrow results
  
  infile.open(filename0+to_string(f)+format);
  
    if(infile.fail()){ // checks to see if file opened 
        
      cout << "error Analysis" << endl; 
        
      return 1; // no point continuing if the file didn't open...
    } 
      
    while(infile >> parh >> jparh) // reads file to end of *file*, not line
    {   
      
      if(jparh == 0){Jet0.push_back(parh);}
      if(jparh == 1){Jet1.push_back(parh);}
  
    } 
  
  infile.close();
  
  
  
  ////////////////////////////////////////////////////////////////////
  //Load quantum D-wave results
  
  
  infile.open(filequantum+to_string(f)+format);
  
    if(infile.fail()){ // checks to see if file opened 
        
      cout << "error Analysis" << endl; 
        
      return 1; // no point continuing if the file didn't open...
    } 
      
    while(infile >> particle_id >> partition_bool) // reads file to end of *file*, not line
    {   
      
      if(partition_bool == -1){
        
        partition0.push_back(particle_id);
      
      }else{
       
        partition1.push_back(particle_id);
      
      }  
  
    } 
  
  infile.close(); 
  
  
  
  ///////////////////////////////////////////////////////////
  //RELATIVE EFFICIENCY
  // Compare results: #particles in jet0 that also are in same partition/#total n. of particles in jet0
  
  n_successes0 = 0;
  n_successes1 = 0;

  for(int i = 0; i < Jet0.size(); i++){
  
    ans0 = find(partition0.begin(), partition0.end(), Jet0[i]);
    ans1 = find(partition1.begin(), partition1.end(), Jet0[i]);
  
    if(ans0 != partition0.end()){
      n_successes0++;
    }
  
    if(ans1 != partition1.end()){
      n_successes1++;
    }
  
  }
  
  success0 = n_successes0*100/Jet0.size();
  success1 = n_successes1*100/Jet0.size();
  
  cout << "Partition 0: " << success0 << "%" << endl;
  cout << "Partition 1: " << success1 << "%" << endl;
  

  n_successes00 = 0;
  n_successes11 = 0;
  
  for(int i = 0; i < Jet1.size(); i++){
  
    ans00 = find(partition0.begin(), partition0.end(), Jet1[i]);
    ans11 = find(partition1.begin(), partition1.end(), Jet1[i]);
  
    if(ans00 != partition0.end()){
      n_successes00++;
      // cout << "found " << Jet1[i] << "in partition 0" << endl;
    }
  
    if(ans11 != partition1.end()){
      n_successes11++;
      // cout << "found " << Jet1[i] << "in partition 1" << endl;
    }
  
  }
  
  success00 = n_successes00*100/Jet1.size();
  success11 = n_successes11*100/Jet1.size();
  
  cout << "Partition 0 jet1: " << success00 << "%" << endl;
  cout << "Partition 1 jet1: " << success11 << "%" << endl;
  

  if( (max(n_successes0,n_successes1) == n_successes0 && max(n_successes00,n_successes11) == n_successes00) || (max(n_successes0,n_successes1) == n_successes1 && max(n_successes00,n_successes11) == n_successes11)){
    eff = 0;
  }else{
    eff = 100*(max(n_successes0,n_successes1) + max(n_successes00,n_successes11))/(Jet0.size()+Jet1.size());
  }
  cout << eff << endl;
  Eff.push_back(eff);  
    
///////////////////////Clear SHIT

  cout << endl;
  
  Jet0.clear();
  Jet1.clear();
  partition0.clear();
  partition1.clear();

  }

int sum = 0;

for(int i=0; i < Eff.size(); i++){

  sum = sum + Eff[i];

}

cout << sum/Eff.size() << endl;
Eff.clear();
  
}
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  