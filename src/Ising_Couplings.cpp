#include <iostream>
#include <fstream>
#include <istream>
#include <vector>
#include <math.h>

using namespace std;

double d(double px1, double py1, double pz1, double px2, double py2, double pz2){

	return sqrt((px1-px2)*(px1-px2) + (py1-py2)*(py1-py2) + (pz1-pz2)*(pz1-pz2));
}

double theta(double px1, double py1, double pz1, double px2, double py2, double pz2){

	double dot = px1*px2 + py1*py2 + pz1*pz2;
	double norm1 = sqrt(px1*px1 + py1*py1 + pz1*pz1);
	double norm2 = sqrt(px2*px2 + py2*py2 + pz2*pz2);

	//double theta = acos(dot/(norm1*norm2));
	double cos = dot/(norm1*norm2);

	// if(theta > M_PI){
	// 	theta = 2*M_PI-theta;
	// 	cout << "yah" << endl;
	// }

	return -cos;
}

int main() {

vector<int> id;
vector<double> px;
vector<double> py;
vector<double> pz;
vector<double> E;
vector<double> m;

int ID, STATUS, file_n, count;
double PX, PY, PZ, e, M;

// Read from Pythia data file 

ifstream infile;   
ofstream J_write;

infile.open("/Users/diogopires/Desktop/jets/Diogo/Events/file_n.txt");
infile >> file_n;
infile.close();

string format(".txt");
string filename("/Users/diogopires/Desktop/jets/Diogo/Events/Ising_test");
string Jfile("/Users/diogopires/Desktop/jets/Diogo/Events/J-matrix");

vector<double> J;


for(int f = 30; f < file_n; f++){

  infile.open(filename+to_string(f)+format);// file containing numbers in 3 columns 
     if(infile.fail()) // checks to see if file opened 
    { 
      cout << "error J_Matrix" << endl; 
      return 1; // no point continuing if the file didn't open...
    } 
       while(infile >> ID >> STATUS >> PX >> PY >> PZ >> e >> M) // reads file to end of *file*, not line
      { 	

        id.push_back(ID);
        px.push_back(PX);
 		py.push_back(PY);
 		pz.push_back(PZ);
		E.push_back(e);
		m.push_back(M);

      }


  infile.close(); 

  J_write.open(Jfile+to_string(f)+format);
  J_write << "{";

  count = 0;
	/// Dot Product J-matrix

	long J_size = px.size()*px.size();
	
	for(int i = 0; i<px.size()-1; i++){
		
		for(int j = i+1; j<px.size(); j++){
	
			//J.push_back(0.5*d(px[i],py[i],pz[i],px[j],py[j],pz[j]));

			J.push_back(0.5*theta(px[i],py[i],pz[i],px[j],py[j],pz[j]));
			
			if (i+1 == px.size()-1 && j+1 == px.size()){
				J_write << "('x" << i+1 << "', 'x" << j+1 << "'): " << J[count];
			}else{
				J_write << "('x" << i+1 << "', 'x" << j+1 << "'): " << J[count] << ", ";
			}
			
			count++;
				
		}
	}
	
	J_write << "}";
	J_write.close();


  id.clear();
  px.clear();
  py.clear();
  pz.clear();
  E.clear();
  m.clear();
  J.clear();

}

  	
}
