//===== To demo data transfer in unreliable network code using CRC (16-bits) Technique.

#include<stdio.h>

#include<string.h>

#define N strlen(g)
 
char t[28];//stores test data
char cs[28]; //stores crc checksum
char g[]="10001000000100001"; //generator polynomial
int a,e,c;
 
void xor()
{
    for(c = 1;c < N; c++)   // do xor operation from index 1 till N-1
    cs[c] = (( cs[c] == g[c])?'0':'1'); 
}
 
void crc()
{
    for(e=0;e<N;e++)
        cs[e]=t[e];   //copy the padded data to cs array
    do{
        if(cs[0]=='1')  // if the first element is 1 , only then go ahead with xor operation
            xor(); //xor with generator polynomial 
        for(c=0;c<N-1;c++)
            cs[c]=cs[c+1]; // as we are not doing xor operation for the 0th index , we just push it out from the existing cs array and make the 1st index as the 0th index.
        cs[c]=t[e++]; // as we pushed the element at the 0th index out , we take the next element from the padded data to our xor operand.
    }while(e<=a+N-1); // we continue this process till all the extra elements from the padded data are added to our xor operand and the division process is complete.
}
 
int main()
{
    printf("\nEnter data : ");
    scanf("%s",t);
    printf("\n----------------------------------------");
    printf("\nGeneratng polynomial : %s",g);
    a=strlen(t);
    for(e=a;e<a+N-1;e++)
        t[e]='0';
    printf("\n----------------------------------------");
    printf("\nPadded data is : %s",t);
    printf("\n----------------------------------------");
    crc();
    printf("\nChecksum is : %s",cs);
    for(e=a;e<a+N-1;e++)
        t[e]=cs[e-a];
    printf("\n----------------------------------------");
    printf("\nFinal codeword is : %s",t);
    printf("\n----------------------------------------");
    printf("\nTest error detection 0(yes) 1(no)? : ");
    scanf("%d",&e);
    if(e==0)
    {
        do{
            printf("\nEnter the position where error is to be inserted : ");
            scanf("%d",&e);
        }while(e==0 || e>a+N-1);
        t[e-1]=(t[e-1]=='0')?'1':'0';
        printf("\n----------------------------------------");
        printf("\nErroneous data : %s\n",t);
    }
    crc();
    for(e=0;(e<N-1) && (cs[e]!='1');e++){}  // checksum (i.e cs array ) should have all zeroes after performing crc operation, so if any 1 is found e is not incremented and hence e will become less than N-1 and therefore we can say there is an error in the transmitted message.
        if(e<N-1)
            printf("\nError detected\n\n");
        else
            printf("\nNo error detected\n\n");
            printf("\n----------------------------------------\n");
        return 0;
}
