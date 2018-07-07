#include<iostream>
#include<stdlib.h>

using namespace std;

class atom{
public:
    string name;
    int countA;
    int visited;
    atom(){
        name="";
        countA=0;
        visited=0;
    }
    atom(string a){
        name=a;
        countA=1;
        visited=0;
    }
};

atom grid[5][5];

void printGrid(){
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++)
            if(grid[i][j].countA)
                cout<<grid[i][j].name<<"-"<<grid[i][j].countA<<"\t ";
        else
                cout<<"  "<<"-"<<" "<<"\t ";
        cout<<"\n";
    }
}

int outOfBounds(int i,int j){
    if(i>=5 or j >=5)
        return 1;
    if(i<0 or j<0)
        return 1;
    return 0;
}
int countPerpendicular(int i,int j){
    // for  i,j there are four positions are (i+1,j),(i-1,j),(i,j+1),(i,j-1)
    int perCount=0;
    int ii,jj;
    ii=i+1,jj=j;
    if(!outOfBounds(ii,jj))
        perCount++;

    ii=i-1,jj=j;
    if(!outOfBounds(ii,jj))
        perCount++;

    ii=i,jj=j+1;
    if(!outOfBounds(ii,jj))
        perCount++;

    ii=i,jj=j-1;
    if(!outOfBounds(ii,jj))
        perCount++;
    return perCount;
}

int isCritical(int i,int j){
    int criticalMass=countPerpendicular(i,j);
    //cout<<"\n DUBUG "<<i+1 <<" "<<j+1<<" "<<criticalMass;
    if(grid[i][j].countA<criticalMass)
        return 0;
    return 1;

}

void explode(int i,int j){
    cout<<"\n Possible Explosion at "<<i+1 <<" "<<j+1<<" "<<grid[i][j].name<<" " << grid[i][j].countA<<endl;
    if(!isCritical(i,j) || grid[i][j].visited==1)
        return;
    cout<<"\nExplosion at "<<i+1 <<" "<<j+1<<endl;
    int ii,jj;
    ii=i+1,jj=j;
    string name=grid[i][j].name;
    grid[i][j].name="";
    grid[i][j].visited=1;
    grid[i][j].countA=0;

    if(!outOfBounds(ii,jj)){
        grid[ii][jj].name=name;
        grid[ii][jj].countA++;
        explode(ii,jj);
    }

    ii=i-1,jj=j;
    if(!outOfBounds(ii,jj)){
        grid[ii][jj].name=name;
        grid[ii][jj].countA++;
        explode(ii,jj);
    }

    ii=i,jj=j+1;
    if(!outOfBounds(ii,jj)){
        grid[ii][jj].name=name;
        grid[ii][jj].countA++;
        explode(ii,jj);
    }

    ii=i,jj=j-1;
    if(!outOfBounds(ii,jj)){
        grid[ii][jj].name=name;
        grid[ii][jj].countA++;
        explode(ii,jj);
    }
    grid[i][j].visited=0;
}


void insertAtomAt(string name,int i,int j){
    if((grid[i][j].name==name) || (grid[i][j].name==string(""))){
        grid[i][j].name=name;
        grid[i][j].countA++;
        if(isCritical(i,j)){
            explode(i,j);
        }
    }
    else{
        cout<<"\n Avoiding insertion due to clash of different atoms\n";
    }
    cout<<"\n After Insertion \n";
    printGrid();
    return ;
}

void insertAtom(){
    string name;
    int i,j;
    cout<<"Enter the Name:";
    cin>>name;
    cout<<"Enter the co-ordinates(col,row):";
    cin>>j;
    cin>>i;
    i--;
    j--;
    insertAtomAt(name,i,j);
}


int main(){
    cout<<"Initial Grid\n";
    printGrid();
    int n;
    cout<<"\n Enter the no of insertions:";
    cin>>n;
   while(n!=0){
        insertAtom();
        n--;
   }
    printGrid();
    return 1;
}


