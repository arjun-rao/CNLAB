//To demonstrate leaky bucket algorithm

#include <iostream>
#include <cstdio>
#include <cstdlib>

#define MAXPACKETS 10

using namespace std;
void leakybucket(int bmax, int rate)
{            
    int curr_packet, buffersize=0;
    int pmax = bmax+0.3*bmax;    

    srand(time(NULL));
    for(int i=0;i<MAXPACKETS;i++)
    {
        cout<<"\nIncoming Packet Size:";
        curr_packet = rand()%pmax+10;
        cout<<curr_packet;
        //add packet to buffer
        if(curr_packet+buffersize > bmax)
        {
            cout<<"\nInsufficient Space: packet dropped";
        }
        else 
        {
            cout<<"\nAdded packet with size:"<<curr_packet;            
            buffersize += curr_packet;            
        }        
        cout<<"\nSize of Buffer:"<<buffersize;
        
        cout<<"\nPress any key to continue...";
        getchar();
        
        //Send packets:

        if(!buffersize){
            cout<<"\nBuffer empty";         
        }
        if(buffersize >= rate)    
        {
            buffersize -= rate;
            cout<<endl<<rate<<" bytes sent" <<endl;
        } 
        else
        {
            cout<<endl<<buffersize<<" bytes sent"<<endl;
            buffersize = 0;
        }
    }
    cout<<endl;
    while(buffersize)
    {        
        if(buffersize >= rate)    
        {
            buffersize -= rate;
            cout<<endl<<rate<<" bytes sent" <<endl;
        } 
        else
        {
            cout<<endl<<buffersize<<" bytes sent"<<endl;
            buffersize = 0;
        }
        cout<<"Size of Buffer:"<<buffersize<<endl;
    }
    cout<<"\nNo more data...\n";    
}
int main()
{
    int bufferMax, outRate;
    cout<<"Enter bufferSize,output rate:";
    cin>>bufferMax>>outRate;
    leakybucket(bufferMax,outRate);
    
    return 0;
}

