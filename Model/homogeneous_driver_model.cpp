//---------- This code was written by Sabiha Majumder in 2015------------------------------//

// It simulates a celular automaton model by Lubeck(2006). Also see Sankaran et. al. (2017) for model details.

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
#define p_range 1000   // no. of p values in the range 0-1. This means p runs from 0 to 0.999 by increment of 0.001      
#define T 70000      // No. of time steps to run simulations for each parameter value
#define rep 1  // No. of replicates 



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

//=========================average along rows======================//
// If you have a matrix with each row as different realization, this function will give the average over all the realizations.

void average_along_row(float* A,float*A1){
	int l,k;
	float sum=0;
	
	for(k=0;k<p_range;++k){
		sum=0;
		for(l=0;l<rep;++l){
			sum+=A[l*p_range+k];
		}
		A1[k]=sum/rep;
	}

}	

//====================select random site==============================//
void select_neighbor_of_site(int i ,int j , int*neighbor){
	int left,right,bottom,top ;
	int in = i ,jn = j;

	float test = rand()/(float)RAND_MAX ;
	
	if (i==0) top=N-1;
	else top = i-1;
	
	if (i==N-1) bottom = 0;
	else bottom = i+1 ;
	
	if (j==0) left = N-1;
	else left = j-1 ;
	
	if (j==N-1) right = 0;
	else right = j+1;
				
	if (test <= 0.25) in = top;
	else if ( test <= 0.5) in = bottom;
	else if ( test <=0.75) jn =left;
	else jn = right;
	
	neighbor[0] = in;
	neighbor[1] = jn;
	
}

//========select neighbor of pair=====================================//
int select_neighbor_of_pair(int in ,int jn, int i, int j){
	int left,right,top,bottom,leftn,rightn,topn,bottomn , neighbor_of_pair;
	
	if (i==0) top=N-1;                 //periodic boundary
	else top = i-1;
	
	if (i==N-1) bottom = 0;
	else bottom = i+1 ;
	
	if (j==0) left = N-1;
	else left = j-1 ;
	
	if (j==N-1) right = 0;
	else right = j+1;
	
	if (in==0) topn=N-1;
	else topn = in-1;
	
	if (in==N-1) bottomn = 0;
	else bottomn = in+1 ;
	
	if (jn==0) leftn = N-1;
	else leftn = jn-1 ;
	
	if (jn==N-1) rightn = 0;
	else rightn = jn+1;
	
	int nn[6] ,c=0;
	
	if ((top*N +j) != (in*N+jn)) {
		nn[c]=top*N + j;
		c+=1;
	}
	if ((bottom*N + j) != (in*N+jn)) {
		nn[c]=bottom*N  + j;
		c+=1;
	}
	if ((i*N +right) != (in*N+jn)) {
		nn[c]= i*N + right;
		c+=1;
	}
	if ((i*N +left) != (in*N+jn)) {
		nn[c] = i*N + left;
		c+=1;
	}
	if ((topn*N +jn) != (i*N+j)) {
		nn[c]=topn*N + jn;
		c+=1;
	}
	if ((bottomn*N +jn) != (i*N+j)) {
		nn[c]=bottomn*N  + jn;
		c+=1;
	}
	if ((in*N +rightn) != (i*N+j)) {
		nn[c]= in*N + rightn;
		c+=1;
	}
	if ((in*N +leftn) != (i*N+j)) {
		nn[c] = in*N + leftn;
		c+=1;
	}
	
	float test =rand()/(float)RAND_MAX ;
	
	if (test <=(0.1666)) neighbor_of_pair= nn[0];
	else if ( test <= (2*0.1666)) neighbor_of_pair= nn[1];
	else if ( test <= (3*0.1666)) neighbor_of_pair= nn[2];
	else if ( test <= (4*0.1666)) neighbor_of_pair= nn[3];
	else if ( test <= (5*0.1666)) neighbor_of_pair= nn[4];
	else neighbor_of_pair = nn[5];
	

return neighbor_of_pair;

} 


			
		
////////////// main function //////////////////////////////////
int main(){
	
	srand(time(NULL));
	int x,l,t,i,j,z;
	float p[p_range], q=0.0;
	float  mean;
	
	int* neighbor = new int[2];
	
	for(i=0;i<p_range;++i) {
		p[i]= i/(float)p_range;
	}
	 
	int*A = new int[N*N];


	for(x=p_range;x>-1;x--){   // starting from higest value of p, this loop calculates steady-state density for all p values till 0 
	
			create_random_matrix(A,0.5);  // Initial condition is randomly distributed agents with 50% cover
	
			for(t=0;t<T;t++){
		
				for(z=0;z<N*N ; ++z){                // so that each site gets selected once on an average
				
					i = rand()%N;           // selecting one random site
					j = rand()%N;
					
					float test = rand()/(float)RAND_MAX;
					float test1 = rand()/(float)RAND_MAX;
					
					if (A[i*N+j]==1){     //if the site is occupied
						
						select_neighbor_of_site(i, j ,neighbor);    //look for a neighbor
						int in = neighbor[0] , jn = neighbor[1];
						
						if (A[in*N +jn]==0) {                     //if neighbor is empty
							if (test < p[x]) 
								A[in*N+jn]=1;                 //regular cp
							else A[i*N+j]=0;
						} 

						else {							  
							if (test < q){
								
								int neighbor_of_pair=select_neighbor_of_pair (in, jn, i, j);  //look for the neighbor of pair 
								A[neighbor_of_pair]=1;
							}
							else if (test1 < 1-p[x] )
								A[i*N+j]=0;	
						}
					}
					

				}	
				
			}
			
			mean = density(A);   

			cout<< p[x]<<"\t"<<mean<<endl;  // output value of p and corresponding steady-state density for a given value of q.
			
	//====================saving data in a file======================//
			ofstream spatial_structure_fout;
			ofstream mean_cover_fout;
			
			
			spatial_structure_fout.open("save_snapshots.dat",ios::app);
			mean_cover_fout.open("mean_cover.dat",ios::app);
			

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
	delete[] neighbor;
	return 0;
}
