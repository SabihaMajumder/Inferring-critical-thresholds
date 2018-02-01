//------------------This code was written by Sabiha Majumder in 2014-----------------------//
// It simulates a cellular automaton model. See Kefi et. al. (2007) Nature, Scneider & Kefi (2017), Theoretical Ecology for model details


#include <iostream>
#include <math.h>
using std::cerr;
using namespace std;
#include <fstream>
using std::ofstream;
#include <cstdlib>       // for exit function
#include <ctime>


// parameter definitions
#define L 512
#define m 0.05         // mortality rate
#define g 0.2		  // spatial stress
#define f 0.9         // Local facilitation strength
#define b_range 100         // (=beta*epsilon) Measures the severity of environmental conditions ( Lower b value means higher aridity)
#define delta 0.1     // Fraction of seeds globally dispersed
#define c 0.3         // (=beta*g) where g is the strength dependence.
#define r 0.0001      // regeneration probability of a {-1} site without vegetated sites in the neighbourhood
#define d 0.2         // degadation probability of {0} sites
#define T 100000       // No. of time steps
#define deltat 0.1

// other definitions
#define index i*L+j  // This is the index for a cell in ith row and j th column




//====== function to initialize the matrix ===============//
void create_random_matrix(int*U,float x,float y) {  
	// x is the initial density of vegetation, y is the initial density of degraded sites. 1-x-y is the initial density of empty 		   sites.
	
	int i1, i2;
	
	for (i1 = 0; i1 < L; i1++) {
		for (i2 = 0; i2 < L; i2++) {
		float number = rand()/(float)RAND_MAX;
			if (number<x) U[i1*L+i2]=1;
			else if (number < x+y) U[i1*L+i2]=-1;
			else U[i1*L+i2]=0;
		
		}
		
	}

}

//============ function to duplicate the matrix===========//
void duplicate(int*A,int*A1){
	int i,j;
	
	for(i=0;i<L;++i){
		for(j=0; j<L ;++j){
			A1[index]=A[index];
		}
	}
}

//=======================average density=========================//
double density(int* A){
	int i,j;
	double sum=0; 
	for(i=0;i<L;++i){
		for(j=0;j<L;++j){
			if(A[index]==1){
				sum+=1;
			}
		}
	}
	double average= sum/(L*L);
return average;
}

//====================local density==============================//
double local_density(int*A, int i, int j ){
	int left,right,bottom,top ;
	int in = i ,jn = j;
	double q;
		
	if (i==0) top=L-1;
	else top = i-1;
	
	if (i==L-1) bottom = 0;
	else bottom = i+1 ;
	
	if (j==0) left = L-1;
	else left = j-1 ;
	
	if (j==L-1) right = 0;
	else right = j+1;
				
	q=0;		
	if (A[top*L +j]==1) q=q+1;      // calculating local density
	if (A[bottom*L +j]==1) q=q+1; 
	if (A[i*L +right]==1) q=q+1; 
	if (A[i*L +left]==1) q=q+1; 
	q=q/4;
	
return q;	
	
}


	
////////////// main function //////////////////////////////////
int main(){
	
	srand(time(NULL));
	int x,l,t,i,j,z;
	float b[b_range];
	double mean;
	
	for(i=0;i<b_range;++i){
		b[i]= i/(float)b_range;
	}
	
	double rho, q; 
	int*A= new int[L*L];
	
	
	mean = density(A);
	for(x=0;x<b_range;++x){
		
		create_random_matrix(A,0.3,0.2);  // See the function described above 
		
		for(t=0;t<T;t++){
			rho=density(A);
			if (rho==0) break;
			
			for(z=0; z<(L*L) ;++z){                // so that each site gets selected once on an average
				
				i = rand()%L;           // selecting one random site
				j = rand()%L;
					
				q =local_density(A, i, j);                       
					
				double germination= ((delta*rho) + (1-delta)*q)*(b[x]-(c*rho));   // germination prob.
				double regeneration=(r+(f*q)); 
				double mortality = m+g*(1-q) ;                           // regeneration prob.  g=0 reduces this model to Kefi et. al. 2007 Model     
					
				double test = rand()/(double)RAND_MAX;
				if (germination*deltat > 1) cout<<"decrease deltat";
				if (regeneration*deltat > 1)cout<<"decrease deltat";
				if (mortality*deltat >1) cout<<"decrease deltat";
				if (d*deltat > 1) cout<<"decrease deltat";
					
				if (A[index]==1){
					if (test < mortality*deltat) A[index]=0;
				}
				else if (A[index]==-1){
					if (test < regeneration*deltat) A[index]=0;
				}
				else{
					if (test < germination*deltat) A[index]=1;
					else if (test > 1-d*deltat)  A[index]=-1; 
				}
					
			}	
				
		}
				
		mean = density(A);   
		cout<< b[x]<<"\t"<<mean<<endl;
			

				
	//====================saving data in a file======================//
		ofstream spatial_structure_fout;
		ofstream mean_cover_fout;
			
		spatial_structure_fout.open("snapshots.dat",ios::app);
		mean_cover_fout.open("density.dat",ios::app);
			
		
			
		for(i=0;i<L;++i){
			for(j=0; j<L ;++j){
				spatial_structure_fout<< A[i*L+j]<< endl;
			}
		}
			
		mean_cover_fout << mean << endl;
			
			
		spatial_structure_fout.close();
		mean_cover_fout.close();

		
	}
	
	delete[] A;
		
	return 0;
}
