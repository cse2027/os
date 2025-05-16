#include<stdio.h>
void main(){
int pid[10];
int at[10],bt[10],star[10],tat[10],finish[10];
int wt[10],i,n,totwt=0,totat=0;
printf("Enter no of processes\n");
scanf("%d",&n);
for(i=0;i<n;i++){
printf("Enter process name, arrival time and burst time\n");
scanf("%d%d%d",&pid[i],&at[i],&bt[i]);
}
for(i=0;i<n;i++){
if(i==0){
star[i]=at[i];
wt[i]=star[i]-at[i];
finish[i]=star[i]+bt[i];
tat[i]=finish[i]-wt[i];
totwt=star[i];
}
else{
star[i]=finish[i-1];
wt[i]=star[i]-at[i];
finish[i]=star[i]+bt[i];
tat[i]=finish[i]-at[i];
totwt=totwt+star[i];
}
}
totat=totwt/n;
printf("Total waiting time = %d\nAverage waiting time = %d\n",totwt,totat);
}
