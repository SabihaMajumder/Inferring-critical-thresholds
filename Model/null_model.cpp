//----------------This code was written by Sabiha Majumder in 2015--------------------------//
//It generates landscapes with randomly distributed individuals in space with density 'p'

#include <iostream>
#include <math.h>
using std::cerr;
using namespace std;
#include <fstream>
using std::ofstream;
#include <cstdlib>       // for exit function
#include <ctime>


// parameter definitions
#define N 512    // system size
#define p_range 1000   // no. of p values in range 0-1      
#define T 5000      // No. of time steps
#define rep 1



//====== function to initialize the matrix ===============//
// This function creates a matrix with entries 0's and 1's. Here x is the proportion of 1's

void create_random_matrix(int*U,float x) {  

	int i1, i2;
	
	for (i1 = 0; i1 < N; i1++) {
		for (i2 = 0; i2 < N; i2++) {
			float number = rand()/(float)RAND_MAX;
			if (number<x) U[i1*N+i2]=1;
			else U[i1*N+i2]=0;
		}
	}

}


//=======================average density=========================//
// Calculates the proportion of 1's in the given matrix
float density(int* A){
	int i,j;
	float sum=0; 
	for(i=0;i<N;++i){
		for(j=0;j<N;++j){
			sum+= A[i*N+j];
		}
	}
	float average= sum/(N*N);
return average;
}



		
////////////// main function //////////////////////////////////
int main(){
	
	srand(time(NULL));
	int x,l,t,i,j,z;
	float p[p_range];
	float  mean;
	
	for(i=0;i<p_range;++i) {
		p[i]= i/(float)p_range;
	}
	 
	int*A = new int[N*N];

	
	for(x=0;x<p_range;x++){
	
		create_random_matrix(A,0.5);
			
			for(t=0;t<T;t++){
		
				for(z=0;z<N*N ; ++z){                // so that each site gets selected once on an average
				
					i = rand()%N;           // selecting one random site
					j = rand()%N;
					
					float test = rand()/(float)RAND_MAX;
					float test1 = rand()/(float)RAND_MAX;
					
					if (A[i*N+j]==0){     //if the site is unoccupied
						if (test < p[x]) A[i*N+j]=1;      //occupy it   
					}        
					else{ 					//if the site is occupied
						if (test1 < 1-p[x]) A[i*N+j]=0;     // make it empty 
					} 

						
				}
					

			}	
				
			
			mean = density(A);   
			
			
			cout<< p[x]<<"\t"<<mean<<endl;
			
	
	//====================saving data in a file======================//
			ofstream spatial_structure_fout;
			ofstream mean_cover_fout;
			
			spatial_structure_fout.open("snapshots.dat",ios::app);
			mean_cover_fout.open("density.dat",ios::app);
			
			for(i=0;i<N;++i){
				for(j=0; j<N ;++j){
					spatial_structure_fout<< A[i*N+j]<< endl;
				}
			}
			
			mean_cover_fout << mean << endl;
			
			spatial_structure_fout.close();
			mean_cover_fout.close();
	
	} 
	
	
	delete[] A;
	return 0;
}
