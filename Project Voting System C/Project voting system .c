// Online C compiler to run C program online
#include <stdio.h>
int i;
char winner,runnerUp,loser;
int winnerVotes,runnerUpVotes,loserVotes;
void voteMsg(char participant) {
    printf("    ***   Vote no %d goes to %c    ***\n\n",i,participant);
}
void resultDecider(char p1,char p2,char p3,int wV,int rV,int lV) {
    winner=p1;
    runnerUp=p2;
    loser=p3;
    winnerVotes=wV;
    runnerUpVotes=rV;
    loserVotes=lV;
}
void main() {
    int a=0,b=0,c=0;
    int participant;
    int numberOfVoters;
    printf("Enter how many voters are participating in vote?\n");
    scanf("%d",&numberOfVoters);
    printf("There are 3 participants a person can vote for. They are a,b and c. Also there are %d voters and each person can vote for only one of the 3 participants. Type the index number of the perticipant you want to vote for. \nIf you want to vote a then type 1, type 2 for b and 3 for c\nParticipants :\n1. a\n2. b\n3. c\n",numberOfVoters);
    for(i=1;i<=numberOfVoters;i++) {
        printf("Vote no %d for ",i);
        VoteAgain:
        scanf("%d",&participant);
        switch(participant) {
            case 1:
               voteMsg('a');
               a++;
               break;
            case 2:
               voteMsg('b');
               b++;
               break;
            case 3:
               voteMsg('c');
               c++;
               break;
            default:
               printf("Invalid input. You can enter either 1,2 or 3\nEnter vote no %d again : \n",i);
               goto VoteAgain;
        }
   }
   if(a==b && a==c) {
       printf("a,b and c all of them got equal votes. Winner and loser unidentified");
   }
   else if(c>a && a==b) {
       printf("c is the winner with %d votes\na and b got equal votes of %d. Loser unidentified",c,a);
   }
   else if(a>b && b==c) {
       printf("a is the winner with %d votes\na and b got equal votes of %d. Loser unidentified",a,b);
   }
   else if(b>a && a==c) {
       printf("b is the winner with %d votes\na and c got equal votes of %d. Loser unidentified",b,a);
   }


   else if(c<a && a==b) {
       printf("c is the loser with %d votes\na and b got equal votes of %d. Winner unidentified",c,a);
   }
   else if(a<b && b==c) {
       printf("a is the loser with %d votes\na and b got equal votes of %d. Winner unidentified",a,b);
   }
   else if(b<a && a==c) {
       printf("b is the loser with %d votes\na and c got equal votes of %d. Winner unidentified",b,a);
   }
   else {
       //When all of them got unique number of votes
       if(a>b && b>c) {
           resultDecider('a','b','c',a,b,c);
       }
       else if (c>b && b>a) {
           resultDecider('c','b','a',c,b,a);
       }
       else if(b>c && c>a){
           resultDecider('b','c','a',b,c,a);
       }
       else if(a>b && c>b){
           resultDecider('a','c','b',a,c,b);
       }
       else if(b>a && a>c){
           resultDecider('b','a','c',b,a,c);
       }
       else if(c>a && a>b){
           resultDecider('c','a','b',c,a,b);
       }
       printf("Result : \n%c is the winner with %d votes\n%c is the runner up with %d votes and \n%c is the loser and in 3rd position with only %d votes\n",winner,winnerVotes,runnerUp,runnerUpVotes,loser,loserVotes);
   }



}













