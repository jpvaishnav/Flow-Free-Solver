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
	pair<int,int> p;
	p.first=-1;
	p.second=-1;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(mat[i][j]!=0 && vis[i][j]==false){
				p.first=i;
				p.second=j;
				return p;
			}
		}
	}
	return p;
}

bool backtracking(int i, int j,
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
	            if(backtracking(p.first,p.second,mat,n,vis,c)){
	            	return true;
	            }
	            vis[i1][j1]=false;
			}
			else if(mat[i1][j1]==0){
				mat[i1][j1]=color;
				if(backtracking(i1,j1,mat,n,vis,color)){
					return true;
				}
				mat[i1][j1]=0;
			}
		}
	}
	vis[i][j]=false;
	return false;
}






bool dfs(int &color,int i,int j,vector<vector<bool> >& vis,
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
				if(dfs(color,i1,j1,vis,mat,n,v)){
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
				if(dfs(mat[i][j],i,j,vis,mat,n,v)==false){
					
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
bool backtrackingForwardChecking(int i, int j,
	vector<vector<int> > & mat, int & n,vector<vector<bool> >& vis, int & color,
	vector<bool> &path){
	vis[i][j]=true;
	cnt++;
	if(deadlock(mat,n,vis,path)){
		//cout<<"deadlock while checking for "<<i<<" "<<j<<"\n";
		vis[i][j]=false;
		return false;
	}
	if(region(mat,n)){
    	//cout<<"returned false in region for "<<i<<" "<<j<<"\n";
    	return false;
    }
	for(int p=0;p<4;p++){
		int i1=i+dx[p];
		int j1=j+dy[p];
		if(valid(i1,j1,n,vis)){
			if(mat[i1][j1]==color){
				vis[i1][j1]=true;
				path[color]=true;
				pair<int,int> p=get_color(mat,n,vis);
				if(p.first==-1 && p.second==-1){
					return true;
				}
	            int c=mat[p.first][p.second];
	            if(backtrackingForwardChecking(p.first,p.second,mat,n,vis,c,path)){
	            	return true;
	            }
	            vis[i1][j1]=false;
	            path[color]=false;
			}
			else if(mat[i1][j1]==0){
				mat[i1][j1]=color;
				if(backtrackingForwardChecking(i1,j1,mat,n,vis,color,path)){
					return true;
				}
				mat[i1][j1]=0;
			}
		}
	}
	vis[i][j]=false;
	return false;
}











pair<int,int> get_color_ordering(vector<vector<int> > & mat, int & n,vector<vector<bool> >& vis){
	
	pair<int,int> p;
	p.first=-1;
	p.second=-1;
	//{-1,-1};
	int maximum=INT_MAX;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(mat[i][j]!=0 && vis[i][j]==false){
				int cur=0;
				for(int z=0;z<4;z++){
					int i1=i+dx[z];
					int j1=j+dy[z];
					if(i1>=0 && j1>=0 && i1<=n-1 && j1<=n-1 && mat[i1][j1]==0){
						cur++;
					}
				}
				if(cur<maximum){
					maximum=cur;
					//p={i,j};
					p.first=i;
					p.second=j;
				}
			}
		}
	}
	return p;
}

bool backtrackingFcOrdering(int i, int j,
	vector<vector<int> > & mat, int & n,vector<vector<bool> >& vis, int & color,
	vector<bool> &path){
	//cout<<"visited "<<i<<" "<<j<<"\n";
	vis[i][j]=true;
	cnt++;
	if(cnt%2==0){
	if(deadlock(mat,n,vis,path)){
		//cout<<"deadlock while checking for "<<i<<" "<<j<<"\n";
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
				pair<int,int> p=get_color_ordering(mat,n,vis);
				//cout<<"color picked "<<p.first<<" "<<p.second<<"\n";
				if(p.first==-1 && p.second==-1){
					return true;
				}
	            int c=mat[p.first][p.second];
	            if(backtrackingFcOrdering(p.first,p.second,mat,n,vis,c,path)){
	            	return true;
	            }
	            vis[i1][j1]=false;
	            path[color]=false;
			}
			else if(mat[i1][j1]==0){
				/*
                st.insert({abs(x-i1)+abs(y-j1),{i1,j1}});
                */
                mat[i1][j1]=color;
				if(backtrackingFcOrdering(i1,j1,mat,n,vis,color,path)){
					return true;
				}
				mat[i1][j1]=0;
			}
		}
	}
	vis[i][j]=false;
	return false;
}
int val(char c){
	if(c=='R'){
		return 1;
	}
	if(c=='.'){
		return 0;
	}
	if(c=='G'){
		return 2;
	}
	if(c=='B'){
		return 3;
	}
	if(c=='Y'){
		return 4;
	}
	if(c=='S'){
		return 5;
	}
	if(c=='I'){
		return 6;
	}
	if(c=='L'){
		return 7;
	}
	if(c=='P'){
		return 8;
	}
	return 0;
}
char val_color(int x){
	if(x==0){
		return '.';
	}
	if(x==1){
		return 'R';
	}
	if(x==2){
		return 'G';
	}
	if(x==3){
		return 'B';
	}
	if(x==4){
		return 'Y';
	}
	if(x==5){
		return 'S';
	}
	if(x==6){
		return 'I';
	}
	if(x==7){
		return 'L';
	}
	if(x==8){
		return 'P';
	}
	if(x==9){
		return 'A';
	}
	if(x==10){
		return 'C';
	}
	if(x==11){
		return 'D';
	}
	if(x==12){
		return 'E';
	}
	if(x==13){
		return 'F';
	}
	if(x==14){
		return 'G';
	}
	return '.';
}
/*
1-R
2-G
3-B
4-Y
5-S
6-I
7-L
8-P

*/
vector<vector<int> > get_level_mat(int n){
	if(n==4){
    	vector<vector<int> > mat(n,vector<int>(n,0));
    	int row=0;
    	ifstream fsp;
              fsp.open("level4.txt");
              string line;
              while(fsp){
                  getline(fsp,line);
                  for(int i=0;i<n;i++){
                  	mat[row][i]=val(line[i]);
                  }
                  row++;
              }
              fsp.close();
              return mat;
    }
    if(n==5){
    	vector<vector<int> > mat(n,vector<int>(n,0));
    	mat[0][0]=1;
    	mat[2][2]=2;
    	mat[3][0]=3;
    	mat[3][1]=2;
    	mat[3][2]=4;
    	mat[3][4]=1;
    	mat[4][0]=4;
    	mat[4][4]=3;
    	return mat;
    }
    if(n==6){
    	vector<vector<int> > mat(n,vector<int>(n,0));
    	mat[0][1]=1;
    	mat[0][2]=2;
    	mat[0][5]=3;
    	mat[2][2]=4;
    	mat[2][3]=5;
    	mat[2][5]=3;
    	mat[3][3]=6;
    	mat[3][5]=2;
    	mat[4][1]=5;
    	mat[4][2]=4;
    	mat[4][4]=6;
    	mat[4][5]=1;
        return mat;
    }
    if(n==7){
    	vector<vector<int> > mat(n,vector<int>(n,0));
    	mat[0][1]=1;
    	mat[0][2]=2;
    	mat[1][2]=3;
    	mat[1][3]=4;
    	mat[1][5]=4;
    	mat[2][2]=5;
    	mat[3][2]=6;
    	mat[3][3]=7;
    	mat[3][5]=5;
    	mat[4][4]=7;
    	mat[4][5]=6;
    	mat[5][2]=3;
    	mat[6][2]=1;
    	mat[6][3]=2;
    	return mat;
    }
    if(n==8){
    	vector<vector<int> > mat(n,vector<int>(n,0));
    	mat[0][4]=1;
    	mat[1][4]=2;
    	mat[1][6]=3;
    	mat[1][7]=4;
    	mat[2][4]=3;
    	mat[2][5]=4;
    	mat[2][7]=2;
    	mat[3][3]=5;
    	mat[3][4]=6;
    	mat[4][4]=5;
    	mat[5][4]=6;
    	mat[7][1]=1;
    	return mat;
    }
    if(n==9){
    	vector<vector<int> > mat(n,vector<int>(n,0));
    	mat[0][0]=1;
    	mat[2][3]=2;
    	mat[3][2]=3;
    	mat[3][5]=4;
    	mat[4][5]=5;
    	mat[5][0]=1;
    	mat[5][2]=4;
    	mat[5][3]=5;
    	mat[5][5]=6;
    	mat[6][0]=7;
    	mat[6][3]=8;
    	mat[7][1]=6;
    	mat[7][5]=7;
    	mat[7][7]=3;
    	mat[8][7]=2;
    	mat[8][8]=8;
        return mat;
    }
	if(n==10){
    	vector<vector<int> > mat(n,vector<int>(n,0));
    	mat[0][0]=1;
    	mat[0][9]=1;
    	mat[1][0]=2;
    	mat[1][3]=2;
    	mat[1][4]=3;
    	mat[2][5]=4;
    	mat[2][6]=6;
    	mat[2][7]=7;
    	mat[2][8]=3;
    	mat[3][1]=6;
    	mat[3][8]=8;
    	mat[4][1]=7;
    	mat[4][8]=9;
    	mat[5][0]=4;
    	mat[5][1]=9;
    	mat[6][0]=10;
    	mat[6][8]=10;
    	mat[7][0]=11;
    	mat[7][8]=11;
    	mat[8][0]=12;
    	mat[8][8]=12;
    	mat[9][0]=13;
    	mat[9][9]=13;
    	mat[9][9]=8;
        return mat;
    }
    if(n==11){
    	vector<vector<int> > mat(n,vector<int>(n,0));
    	mat[0][0]=1;
    	mat[0][10]=1;
    	mat[1][0]=2;
    	mat[1][4]=2;
    	mat[1][5]=3;
    	mat[2][6]=4;
    	mat[2][7]=6;
    	mat[2][8]=7;
    	mat[2][9]=3;
    	mat[3][1]=6;
    	mat[3][9]=8;
    	mat[4][1]=7;
    	mat[4][9]=9;
    	mat[5][0]=4;
    	mat[5][1]=9;
    	mat[5][10]=8;
    	mat[6][0]=10;
    	mat[6][10]=10;
    	mat[7][0]=11;
    	mat[7][10]=11;
    	mat[8][0]=12;
    	mat[10][9]=12;
    	mat[9][0]=13;
    	mat[9][9]=13;
    	mat[10][0]=14;
    	mat[10][8]=14;

        return mat;
    }

}
int main(){
	vector<vector<int> > mat;
     int n;
  //int login();
  //login();
  //will execute after logged in.
  while(1) {
  system("CLS");
     cout << "\n\n\t\t ======  IIT Jodhpur ======";
     cout << "\n\n\t\t ======  Artificial Intelligence(CS323) project ======";
     cout << "\n\n\t\t ======  FLOW FREE SOLVER ======";
     cout <<"\n\n                                          ";
     
     cout << "\n\n\t\t\t  1. CHOOSE PROBLEM";
     cout << "\n\n\t\t\t  2. CHOOSE METHOD";
     //cout << "\n\n\t\t\t  3. SOLVE THE PROBLEM ";
     cout << "\n\n\t\t\t  3. Exit Program ";
     cout<<"\n\n";
     cout<<  " \n\t\t====================================";
     cout << "\n\n\t\t\t Select Your Choice ::";
     
     int choice;
     cin>>choice;
     switch(choice)
     {
      case 1 :
        {   system("CLS");
              cout<<"\n\n\t\t\tChoose any of the level from 4 to 11\n\n";
              
              cin>>n;
              mat.clear();
              mat=get_level_mat(n);
              cout<<"\n\n\t\t\tPuzzle grid loading....... : \n\n";
              	for(int i=0;i<n;i++){
              		cout<<"\t\t\t";
              		for(int j=0;j<n;j++){
              			cout<<val_color(mat[i][j])<<" ";
              		}
              		cout<<"\n";
              	}
              system("PAUSE");
              break;
        }
    
           case 2 :{
              
           	system("CLS");
              cout<<"\n\n\t\t\t Choose one method from the list : \n";
              cout<<"\n\n\t\t\t 1.Backtracking : \n";
              cout<<"\n\n\t\t\t 2.Backtracking + Filtering : \n";
              cout<<"\n\n\t\t\t 3.Backtracking + Filtering +  ordering : \n";
              int temp_var;
             cin>>temp_var;
             switch(temp_var){
              case 1: {
              	vector<vector<bool> > vis(n,vector<bool>(n,false));
	time_t e1,e2;
	time(&e1);
	pair<int,int> p=get_color(mat,n,vis);
	int color=mat[p.first][p.second];
	cnt=0;
	bool res=backtracking(p.first,p.second,mat,n,vis,color);
    cout<<"\n\t\t\t=====Solution exists===== "<<"\n\n\n";
    for(int i=0;i<n;i++){
    	cout<<"\t\t\t";
    	for(int j=0;j<n;j++){
    		cout<<val_color(mat[i][j])<<" ";
    	}
    	cout<<"\n";
    }
    time(&e2);
    cout<<"\n\t\t\t=====Execution time:   "<<setprecision(10)<<difftime(e2,e1)<<" second "<<"\n";
    cout<<"\n\t\t\t=====Total nodes explored:     "<<cnt<<"\n";
              	system("PAUSE");
                break;
              }
              case 2: {
              	vector<vector<bool> > vis(n,vector<bool>(n,false));
	vector<bool> path(n+1,false);
	time_t e1,e2;
	time(&e1);
	pair<int,int> p=get_color(mat,n,vis);
	int color=mat[p.first][p.second];
	cnt=0;
	bool res=backtrackingForwardChecking(p.first,p.second,mat,n,vis,color,path);
    cout<<"\n\t\t\t=====Solution exists===== "<<"\n\n\n";
    for(int i=0;i<n;i++){
    	cout<<"\t\t\t";
    	for(int j=0;j<n;j++){
    		cout<<val_color(mat[i][j])<<" ";
    	}
    	cout<<"\n";
    }
    time(&e2);
    cout<<"\n\n\t\t\t=====Execution time:   "<<setprecision(10)<<difftime(e2,e1)<<" second "<<"\n";
    cout<<"\n\t\t\t=====Total nodes explored:     "<<cnt<<"\n";
              	system("PAUSE");
                break;
                }
              case 3: {

              	m.clear();
              	cn=0;

    for(int i=0;i<n;i++){
    	for(int j=0;j<n;j++){
    		if(mat[i][j]>0){
    			m[mat[i][j]].first=i;
    			m[mat[i][j]].second=j;
    			//{i,j};
    		}
    		cn=max(cn,mat[i][j]);
    	}
    }
    
	vector<vector<bool> > vis(n,vector<bool>(n,false));
	vector<bool> path(cn+1,false);
	//int cnt=0;
	time_t e1,e2;
	time(&e1);
	pair<int,int> p=get_color_ordering(mat,n,vis);
	int color=mat[p.first][p.second];
	cnt=0;
	bool res=backtrackingFcOrdering(p.first,p.second,mat,n,vis,color,path);
	time(&e2);
    cout<<"\n\n\t\t\t=====Solution exists===== "<<"\n\n\n";
    char c=8;
    for(int i=0;i<n;i++){
    	cout<<"\t\t\t";
    	for(int j=0;j<n;j++){
    		cout<<val_color(mat[i][j])<<" ";
    	}
    	cout<<"\n";
    }
    
    cout<<"\n\t\t\t=====Execution time:   "<<setprecision(10)<<difftime(e2,e1)<<" second "<<"\n";
              	cout<<"\n\t\t\t=====Total nodes explored:     "<<cnt<<"\n";
              	system("PAUSE");
                break;
              }
              
              default:{
                cout<<"\n\t\t\t Please select again "<<endl;
                break;
              }
             }
             break;
         }
      case 3: 
       {
        //exiting from the system at the end of the day.
        system("CLS");
        cout<<"\n\n\n\t\t\t Copyright Jay Prakash(B18CSE017), T&C applied \n\t\t\t ";
       exit(0);
        break;
      }
      default : 
       {
       cout<<"\n\n\t\t Invalid input";
      cout<<"\n\n\t\tPress Enter to continue";
    }
   }
//getch();
}
}