#include <iostream> 
#include <stdio.h>                 // Needed for printf() to get nice hex values
#include <stdlib.h>                 // Needed for rand()

using namespace std;

//----- Type defines ----------------------------------------------------------
typedef unsigned char      byte;    // Byte is a char
typedef unsigned short int word16;  // 16-bit word is a short int
typedef unsigned int       word32;  // 32-bit word is an int

//----- Globals ---------------------------------------------------------------
int BUFFER_LEN=4096;      // Length of buffer when using random data

//----- Prototypes ------------------------------------------------------------
word16 checksum(byte *addr, word32 count,word32 initsum = 0);

//===== Main function ==========================================================
int main(void)
{
  byte        buff[BUFFER_LEN]; // Buffer of packet bytes
  word16      check;            // 16-bit checksum value
  word32      i,ch,v=0;                // Loop counter and choice
  
  printf("Use random values(0) or enter data(1) for checksum demo:");
  cin>>ch;

  if(ch){
    printf("Enter the number of bytes:");
    cin>>BUFFER_LEN;
    printf("Enter the %d bytes:",BUFFER_LEN);
    for (i=0; i<BUFFER_LEN; i++)
      cin>>buff[i];
    v = 1;//indicates verbose
  }
  else
  {
    srand(time(NULL));
    // Load buffer with BUFFER_LEN random bytes
    for (i=0; i<BUFFER_LEN; i++)
      buff[i] = (byte) rand();  
  }
  
  if(v) printf("\nOriginal Data:%s\n",buff);  
  // Compute the 16-bit checksum
  check = checksum(buff, BUFFER_LEN);
  printf("\nOriginal checksum of data = %04X\n", check);
  printf("\nTest error detection 0(yes) 1(no)? : ");
  cin>>ch;
  if(ch==0)
  {
    do{
      do{
          printf("\nEnter the position where error is to be inserted(or 0 to stop) : ");
          cin>>ch;
      }while(ch>BUFFER_LEN-1);
      buff[ch]++;
    }while(ch!=0);      
  }
  if(v) printf("\nNew Data:%s\n",buff);
  check = checksum(buff,BUFFER_LEN,check);
  // Output the checksum
  printf("\nValidated checksum = %04X\n", check);
  if(check)
    printf("\nError Detected!\n");
  else
    printf("\nNo errors occured!\n");
}

//=============================================================================
//=  Compute Internet Checksum for count bytes beginning at location addr     
//   Passing initsum in case a checksum needs to be validated.
//=============================================================================
word16 checksum(byte *addr, word32 count,word32 initsum)
{
   word32 sum = initsum;

  // Main summing loop
  while(count > 1)
  {    
    sum = sum + *((word16 *) addr);
    count = count - 2;
    (word16 *) addr++;
  }

  // Add left-over byte, if any
  if (count > 0)
    sum = sum + *((byte *) addr);

  // Fold 32-bit sum to 16 bits
  while (sum>>16)
    sum = (sum & 0xFFFF) + (sum >> 16);

  return(~sum);
}