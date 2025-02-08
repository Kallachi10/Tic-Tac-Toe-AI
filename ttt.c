//ttt.ai using classic minimax algorithm

#include<stdio.h>
#include<stdbool.h>
int flag = 0;
struct board{
    char c;
    int p;
};
struct move{
    int x;
    int y;
};
struct move bestMove;
int wincheck(struct board s[3][3],int a,int b);
int max(int a, int b){
    if (a>=b)
        return a;
    else
        return b;
    
}
int min(int a, int b){
    if(a<=b)
        return a;
    else
        return b;
}
int moveGen(struct board s[3][3],struct move* moves){
   
    int k=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(s[i][j].c=='\0'){
                moves[k].x = i;
                moves[k++].y = j;
            }
        }
    }
    return k;
}
int minimax(int depth,struct board s[3][3],bool isMaximizing,int lastX,int lastY){
    //generate legal moves first
    struct move moves[10];
    int size = moveGen(s,moves);
    int bestScore;
    int result;
    if(lastX!=-1)
        result = wincheck(s,lastX,lastY);
    else
        result = -10;
    if(depth==0||result==-3||result==3||result==9){
        if(result==3)
            return +1;
        else if(result==-3)
            return -1;
        else
            return 0;
    }
    if(flag==0)
        flag = 1;

    if(isMaximizing)
        bestScore = -1000;
    else
        bestScore = 1000;
    
        for(int i = 0;i < size;i++){
            int m = moves[i].x;
            int n = moves[i].y;
            if(isMaximizing){
                s[m][n].c = 'X';
                s[m][n].p = 1;
            }
                
            else{
                s[m][n].c = 'O';
                s[m][n].p = -1;
            }

            int score = minimax(depth-1,s,!isMaximizing,m,n);
            s[m][n].c = '\0';
            s[m][n].p = 0;
            if(isMaximizing){
                if(score>bestScore){
                    bestScore = score;
                    bestMove.x = moves[i].x;
                    bestMove.y = moves[i].y;
                }
            }
                
            else{
                if(score<bestScore){
                    bestScore = score;
                    bestMove.x = moves[i].x;
                    bestMove.y = moves[i].y;
                }
            }
        }
    
    return bestScore;
}
void display(struct board s[3][3]) {
    printf("\n\t 0   1   2\n\n");
    for (int i = 0; i < 3; i++) {
        printf("%d\t", i);
        for (int j = 0; j < 3; j++) {
            printf(" %c ", s[i][j].c ? s[i][j].c : ' '); // Display 'X', 'O', or space
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("  \t---+---+---\n");
    }
    printf("\n");
}



int wincheck(struct board s[3][3],int a,int b){
    
    int sum1=0,sum2=0,d1=0,d2=0,draw=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(s[i][j].p==1||s[i][j].p==-1)
            draw++;
        }
    }
    for(int i=0;i<3;i++){
        sum1=sum1+s[a][i].p;
    }
      for(int i=0;i<3;i++){
        sum2=sum2+s[i][b].p;
      }
     
       
       d1=s[0][0].p+s[1][1].p+s[2][2].p;
       d2=s[0][2].p+s[1][1].p+s[2][0].p;
      
      if(sum1==3||sum1==-3)
      return sum1;
      else if(sum2==3||sum2==-3)
      return sum2;
      else if(d1==3||d1==-3)
      return d1;
      else if(d2==3||d2==-3)
      return d2;
      else if(draw==9)
      return draw;
      else 
        return 0;
      
}

void main(){
    struct board s[3][3]={'\0','\0','\0','\0','\0','\0','\0','\0','\0'};
    display(s);
    int r,c,count=0,k=0,depth = 9;
    while(1){
        if(count%2==0){
            printf("enter position");
            scanf("%d%d",&r,&c);
            s[r][c].c='X';
            count++;
            s[r][c].p=1;
            k=wincheck(s,r,c);
            
        }
        else{
            printf("\n\n%d",bestMove.x);
            int score = minimax(depth-count,s,false,-1,-1);
            printf("\n%d",score);
            r = bestMove.x;
            c = bestMove.y;
            s[r][c].c='O';
            count++;
            s[r][c].p=-1;
            k=wincheck(s,r,c);
        }
        
        display(s);
        if(k==3){
        printf("player 1 wins\n\tCongrats");
        break;
        }
        else if(k==-3){
        printf("player 2 wins\n\tCongrats");
            break;
        }
        else if(k==9){
        printf("\nDRAW!!");
        break;}
        
    }
    
}


