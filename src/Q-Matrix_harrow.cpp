#include <iostream>
#include <fstream>
#include <istream>
#include <vector>
#include <math.h>

using namespace std;

int main() {

vector<int> id;
//vector<string> type;
vector<double> px;
vector<double> py;
vector<double> pz;
vector<double> E;
vector<double> m;

int ID, STATUS, count, file_n;
double PX, PY, PZ, e, M, T_denom = 0;

// Read from Pythia data file 

ifstream infile;   
ofstream Q_write;

infile.open("/Users/diogopires/Desktop/jets/Diogo/Events/file_n.txt");
infile >> file_n;
infile.close();

string format(".txt");
string filename("/Users/diogopires/Desktop/jets/Diogo/Events/Ising_test");
string Qfile("/Users/diogopires/Desktop/jets/Diogo/Events/Q-matrix");


for(int f = 0; f < file_n; f++){

  infile.open(filename+to_string(f)+format);// file containing numbers in 3 columns 
     if(infile.fail()) // checks to see if file opened 
    { 
      cout << "error Q-matrix" << endl; 
      return 1; // no point continuing if the file didn't open...
    } 
       while(infile >> ID >> STATUS >> PX >> PY >> PZ >> e >> M) // reads file to end of *file*, not line
      { 	

        id.push_back(ID);
        //type.push_back(TYPE);
        px.push_back(PX);
 		py.push_back(PY);
 		pz.push_back(PZ);
		E.push_back(e);
		m.push_back(M);

      }


for(int i = 0; i < px.size(); i++){

	T_denom += sqrt(px[i]*px[i] + py[i]*py[i] + pz[i]*pz[i]);
} 

  infile.close(); 

  Q_write.open(Qfile+to_string(f)+format);
  Q_write << "{";

	/// Dot Product Q-matrix

	long Q_size = px.size()*px.size();
	double Q[Q_size];
	
	count = 0;

	for(int i = 0; i<px.size(); i++){
			
		for(int j = 0; j<px.size(); j++){
	
			Q[count] = (-4/(T_denom*T_denom))*(px[i]*px[j] + py[i]*py[j] + pz[i]*pz[j]);
			
			//Q[count] = -(px[i]*px[j] + py[i]*py[j] + pz[i]*pz[j]);

			if (i+1 == px.size() && j+1 == px.size()){
				Q_write << "('x" << i+1 << "', 'x" << j+1 << "'): " << Q[count];
			}else{
				Q_write << "('x" << i+1 << "', 'x" << j+1 << "'): " << Q[count] << ", ";
			}
			
			count++;
				
		}
	}
	
	Q_write << "}";
	Q_write.close();

	id.clear();
  px.clear();
  py.clear();
  pz.clear();
  E.clear();
  m.clear();

}

  	
}
