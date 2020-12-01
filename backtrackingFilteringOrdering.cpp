#include<bits/stdc++.h>
#include<ctime>
#include<stdlib.h>
//#include<conio.h>
//#include<windows.h>
using namespace std;
map<int,pair<int,int> > m;
int cn=0;
int cnt=0;
bool valid(int i, int j, int & n,
	  vector<vector<bool> >& vis){
	return (i>=0 && j>=0 && i<=n-1 && j<=n-1 && vis[i][j]==false);
}

int dx[4]={-1,0,0,1};
int dy[4]={0,-1,1,0};


pair<int,int> get_color(vector<vector<int> > & mat, int & n,vector<vector<bool> >& vis){
	
	pair<int,int> p={-1,-1};
	int maximum=INT_MAX;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(mat[i][j]!=0 && vis[i][j]==false){
				int cur=0;
				for(int p=0;p<4;p++){
					int i1=i+dx[p];
					int j1=j+dy[p];
					if(i1>=0 && j1>=0 && i1<=n-1 && j1<=n-1 && mat[i1][j1]==0){
						cur++;
					}
				}
				if(cur<maximum){
					maximum=cur;
					p={i,j};
				}
			}
		}
	}
	return p;
}

bool dfs(int &color,int i,int j,
	     vector<vector<int> > & mat,int &n,
	     vector<vector<bool> >& v){
	v[i][j]=true;
	for(int p=0;p<4;p++){
		int i1=i+dx[p];
		int j1=j+dy[p];
		if(i1>=0 && j1>=0 && i1<=n-1 && j1<=n-1  && v[i1][j1]==false){
			if(mat[i1][j1]==color){
				
				return true;
			}
			else if(mat[i1][j1]==0){
				if(dfs(color,i1,j1,mat,n,v)){
					return true;
				}
			}
		}
	}
	v[i][j]=false;
	return false;
}

bool deadlock(vector<vector<int> > & mat, int & n,vector<vector<bool> >& vis,
	          vector<bool> & path){
		for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(mat[i][j]>0 && path[mat[i][j]]==false){
				vector<vector<bool> > v(n, vector<bool>(n,false));
				if(dfs(mat[i][j],i,j,mat,n,v)==false){
					
					return true;
				}
			}
		}
	}
	
	
    return false;
}
bool dfs1(int i, int j,vector<vector<int> > & mat, int & n,vector<vector<bool> >& vis, int & cnt){
	vis[i][j]=true;
	for(int p=0;p<4;p++){
		int i1=i+dx[p];
		int j1=j+dy[p];
		if(i1>=0 && j1>=0 && i1<=n-1 && j1<=n-1){
			if(mat[i1][j1]>0){
				cnt++;
			}
			else if(mat[i1][j1]==0 && vis[i1][j1]==false){
				dfs1(i1,j1,mat,n,vis,cnt);
			}
		}
	}
}
bool region(vector<vector<int> > & mat, int & n){
	vector<vector<bool> > vis(n,vector<bool>(n,false));
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(vis[i][j]==false && mat[i][j]==0){
                int cnt=0;
				dfs1(i,j,mat,n,vis,cnt);
				if(cnt==0){
					return true;
				}
			}
		}
	}
	return false;
}
bool solve(int i, int j,
	vector<vector<int> > & mat, int & n,vector<vector<bool> >& vis, int & color,
	vector<bool> &path){
	//cout<<"visited "<<i<<" "<<j<<"\n";
	vis[i][j]=true;
	cnt++;
	if(cnt%2==0){
	if(deadlock(mat,n,vis,path)){
		vis[i][j]=false;
		return false;
	}
    }
	for(int p=0;p<4;p++){
		int i1=i+dx[p];
		int j1=j+dy[p];
		if(valid(i1,j1,n,vis)){
			if(mat[i1][j1]==color){
				vis[i1][j1]=true;
				path[color]=true;
				pair<int,int> p=get_color(mat,n,vis);
				//cout<<"color picked "<<p.first<<" "<<p.second<<"\n";
				if(p.first==-1 && p.second==-1){
					return true;
				}
	            int c=mat[p.first][p.second];
	            if(solve(p.first,p.second,mat,n,vis,c,path)){
	            	return true;
	            }
	            vis[i1][j1]=false;
	            path[color]=false;
			}
			else if(mat[i1][j1]==0){
				
                mat[i1][j1]=color;
				if(solve(i1,j1,mat,n,vis,color,path)){
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
     cout<<"\t\t =====  Solving a grid of 9*9 =====\n\n";
	int n;
	n=9;
	vector<vector<int> > mat(n,vector<int>(n,0));
	mat={{1,0,0,0,0,0,0,0,0},
         {0,0,0,0,0,0,0,0,0},
         {0,0,0,2,0,0,0,0,0},
         {0,0,3,0,0,4,0,0,0},
         {0,0,0,0,0,5,0,0,0},
         {1,0,4,5,0,6,0,0,0},
         {7,0,0,8,0,0,0,0,0},
         {0,6,0,0,0,7,0,3,0},
         {0,0,0,0,0,0,0,2,8}} ;
    
    m.clear();
    for(int i=0;i<n;i++){
    	for(int j=0;j<n;j++){
    		if(mat[i][j]>0){
    			m[mat[i][j]]={i,j};
    		}
    		cn=max(cn,mat[i][j]);
    	}
    }
    
	vector<vector<bool> > vis(n,vector<bool>(n,false));
	vector<bool> path(cn+1,false);
	//int cnt=0;
	time_t e1,e2;
	time(&e1);
	pair<int,int> p=get_color(mat,n,vis);
	int color=mat[p.first][p.second];
	cnt=0;
	bool res=solve(p.first,p.second,mat,n,vis,color,path);
	time(&e2);
    cout<<"\n\n\t\t\t====solution exist==== "<<"\n";
    char c=8;
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