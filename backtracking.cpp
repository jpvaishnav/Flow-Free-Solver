#include<bits/stdc++.h>
#include<ctime>
using namespace std;
int cnt=0;
bool valid(int i, int j, int & n,
	  vector<vector<bool> >& vis){
	return (i>=0 && j>=0 && i<=n-1 && j<=n-1 && vis[i][j]==false);
}

int dx[4]={-1,0,0,1};
int dy[4]={0,-1,1,0};
pair<int,int> get_color(vector<vector<int> > & mat, int & n,vector<vector<bool> >& vis){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(mat[i][j]!=0 && vis[i][j]==false){
				return {i,j};
			}
		}
	}
	return {-1,-1};
}

bool solve(int i, int j,
	vector<vector<int> > & mat, int & n,vector<vector<bool> >& vis, int & color){
	vis[i][j]=true;
	cnt++;
	for(int p=0;p<4;p++){
		int i1=i+dx[p];
		int j1=j+dy[p];
		if(valid(i1,j1,n,vis)){
			if(mat[i1][j1]==color){
				vis[i1][j1]=true;
				pair<int,int> p=get_color(mat,n,vis);
				if(p.first==-1 && p.second==-1){
					return true;
				}
	            int c=mat[p.first][p.second];
	            if(solve(p.first,p.second,mat,n,vis,c)){
	            	return true;
	            }
	            vis[i1][j1]=false;
			}
			else if(mat[i1][j1]==0){
				mat[i1][j1]=color;
				if(solve(i1,j1,mat,n,vis,color)){
					return true;
				}
				mat[i1][j1]=0;
			}
		}
	}
	vis[i][j]=false;
	return false;
}
int main(){
	cout << "\n\n\t\t ======  IIT Jodhpur ======";
     cout << "\n\n\t\t ======  Artificial Intelligence(CS323) project ======";
     cout << "\n\n\t\t ======  FLOW FREE SOLVER ======";
     cout <<"\n\n";
     cout<<"\t\t =====  Solving a grid of 8*8 =====\n\n";
	int n;
	n=8;
	vector<vector<int> > mat(n,vector<int>(n,0));
	mat={{0,0,0,0,1,0,0,0},
         {0,0,0,0,2,0,3,4},
         {0,0,0,0,3,4,0,2},
         {0,0,0,5,6,0,0,0},
         {0,0,0,0,5,0,0,0},
         {0,0,0,0,6,0,0,0},
         {0,0,0,0,0,0,0,0},
         {0,1,0,0,0,0,0,0}};
      
	vector<vector<bool> > vis(n,vector<bool>(n,false));
	time_t e1,e2;
	time(&e1);
	pair<int,int> p=get_color(mat,n,vis);
	int color=mat[p.first][p.second];
	cnt++;
	bool res=solve(p.first,p.second,mat,n,vis,color);
    cout<<"\n\t\t\tsolution exist "<<"\n";
    time(&e2);
    for(int i=0;i<n;i++){
    	cout<<"\t\t\t";
    	for(int j=0;j<n;j++){
    		if(mat[i][j]==1){
    		    //system("Color 0A");
                //printf("\033[;31m %c \033[0m",254);
    		    cout<<"\033[;31mR \033[0m";
    		    //cout<<"\033[;31m"<<c<<"\033[0m";
    		    //cout<<mat[i][j]<<" ";    	
    		}
    		if(mat[i][j]==2){
    		    //system("Color 1A");
    		    cout<<"\033[1;32mG \033[0m";
    		    //cout<<mat[i][j]<<" ";    	
    		}
    		if(mat[i][j]==3){
    		//system("Color 1A");
    		    cout<<"\033[;33mB \033[0m";
    		    //cout<<mat[i][j]<<" ";    	
    		}
    		if(mat[i][j]==4){
    		    //system("Color 1A");
    		    cout<<"\033[;34mY \033[0m";
    		    //cout<<mat[i][j]<<" ";    	
    		}
    		if(mat[i][j]==5){
    		    //system("Color 1A");
    		    cout<<"\033[1;35mS \033[0m";
    		    //cout<<mat[i][j]<<" ";    	
    		}
    		if(mat[i][j]==6){
    		    //system("Color 1A");
    		    cout<<"\033[1;36mI \033[0m";
    		    //cout<<mat[i][j]<<" ";   	
    		}
    		if(mat[i][j]==7){
    		    //system("Color 1A");
    		    cout<<"\033[1;37mL \033[0m";
    		    //cout<<mat[i][j]<<" ";   	
    		}
    		if(mat[i][j]==8){
    		    //system("Color 1A");
    		    cout<<"\033[1;38mP \033[0m";
    		    //cout<<mat[i][j]<<" ";    	
    		}
    		if(mat[i][j]==9){
    		    //system("Color 1A");
    		    cout<<"\033[1;39m9 \033[0m";
    		    //cout<<mat[i][j]<<" ";    	
    		}
    	}
    	cout<<"\n";
    }
    
    cout<<"\n\t\t\t=====Execution time: "<<setprecision(10)<<difftime(e2,e1)<<" second "<<"\n";
    cout<<"\n\t\t\t=====Total nodes explored: "<<cnt<<"\n\n\n\n";
}
