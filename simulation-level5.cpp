#include<iostream>
#include<stdlib.h>
#include<map>
#include<stack>
#include<cmath>

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

class stackNode{
public:
    int i,j;
    stackNode(){}
    stackNode(int ii,int jj){
    i=ii;
    j=jj;
    }
};

stack<stackNode> S;

void explodeQueue(int i,int j){
    if(!isCritical(i,j))
        return;
    if(isCritical(i,j)&&grid[i][j].visited==1){
        S.push(stackNode(i,j));
        return;
    }
    int ii,jj;
    ii=i+1,jj=j;
    string name=grid[i][j].name;
    grid[i][j].name="";
    grid[i][j].visited=1;
    grid[i][j].countA=0;

    if(!outOfBounds(ii,jj)){
        grid[ii][jj].name=name;
        grid[ii][jj].countA++;
        explodeQueue(ii,jj);
    }

    ii=i-1,jj=j;
    if(!outOfBounds(ii,jj)){
        grid[ii][jj].name=name;
        grid[ii][jj].countA++;
        explodeQueue(ii,jj);
    }

    ii=i,jj=j+1;
    if(!outOfBounds(ii,jj)){
        grid[ii][jj].name=name;
        grid[ii][jj].countA++;
        explodeQueue(ii,jj);
    }

    ii=i,jj=j-1;
    if(!outOfBounds(ii,jj)){
        grid[ii][jj].name=name;
        grid[ii][jj].countA++;
        explodeQueue(ii,jj);
    }
    grid[i][j].visited=0;
}

void explode(int i,int j){

    S.push(stackNode(i,j));
    while(!S.empty()){
        stackNode g;
        g.i=S.top().i;
        g.j=S.top().j;
        S.pop();
        explodeQueue(g.i,g.j);
    }
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

void insertAtom(int player){ //player 0 means who plays zo and 1 means Robot
    string name;
    int i,j;
    if(player==0)
        name="zo";
    else
        name="ho";
    if(player==0){
        cout<<"Enter the co-ordinates(col,row) for placing "<<name<<" : ";
        cin>>j;
        cin>>i;
        i--;
        j--;
    }
    else{
        //get the random numbers for i,j;
        i=rand()%5;
        j=rand()%5;
        cout<<"\n Robot Chose "<<i <<" "<< j<<endl;
    }

     insertAtomAt(name,i,j);
}

int whoWon(){
    map<string,int> Pmap;
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            Pmap[grid[i][j].name]+=1;
    if(Pmap[string("ho")]==0 && Pmap[string("zo")]>0)
        return 1; //1 implies Dexter
    if(Pmap[string("zo")]==0 && Pmap[string("ho")]>0)
        return 2; // 2 implies Carol
    return 0;
}



int main(){
    cout<<"Initial Grid\n";
    printGrid();
    int player=0;
    while(1){
        cout<<"\nPlayer "<<player<<" Turn\n";
        insertAtom(player);
        player=(player==0)?1: 0;
        int won=whoWon();
        if(won==0)
            continue;
        string winner=(won==1)?"Dexter":"Carol";
        cout<<"\n Current Board Winner is "<<winner<<endl;
    }
    printGrid();
    return 1;
}


