#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <math.h>
#include "Heap.hpp"
using namespace std;

	/*
	* Constructor Name: Heap()
    * Parameters : MaxHeapSize
    * Description : constructor to initialse the size of the memory block.
    */

    Heap::Heap(int heapsize)
    {
        size=heapsize;
        FreeList = new LinkedList();
    }

    /*
	* Function Name: allocate()
    * Parameters :  NodeSize
    * Return Type : Returns -1 if unable to allocate or else returns the 
    *               allocated start address to the main.
    * Description : Allocates the node of the size mentioned in parameters
    *               and allocates the remaining size to the freelist.
    */
	
    int Heap::allocate(int numBytes)
	{
        int NodeSize=0,address=0;
        NodeSize=numBytes;
        if(NodeSize > size  )
        {
            return -1;
        }
        Node* newnode = new Node();   
        if(liveNodes > 0 && FreeList->countList() == 0)  
        {
            return -1;
        }
        if (FreeList->head == NULL) 
        {    
            if(size-NodeSize == 0)
            {
                address=0;
                liveNodes += 1;
            } 
            else
            {  
                newnode->addr = NodeSize;
                newnode->size = (size-NodeSize);
                newnode->next = NULL;
                FreeList->head = newnode;
                address=0;
                liveNodes += 1;
            }
        }
        else 
        {
            address = FreeList->find_free(NodeSize);
            int c= FreeList->countList();
            if(address == -1)
            { 
                return -1;
            }
            liveNodes += 1; 
            Node* temp = FreeList->head;    
            while (temp->addr != address) 
            { 
                temp = temp->next; 
            }
            if(temp->size == NodeSize && c >= 1)
            {
                FreeList->freeNodeLL(temp->addr);
            } 
            if(temp->size > NodeSize && c >= 1)
            {
                temp->addr = (temp->addr + NodeSize);
                temp->size = (temp->size - NodeSize);
            }      
        }    
        return address;
    }

/*
	* Function Name: free()
    * Parameters :  address,NodeSize
    * Return Type : Returns 0 once freeing is done.
    * Description : Frees up the allocated node and adds it to the free list.
    */

    int Heap :: free (int addrs,int sizef)
    {
        Node* newnode = new Node();
        newnode->size = sizef;
        newnode->addr = addrs;
        //cout << "--\n"; 
        int c = FreeList->countList();
        //cout << "\ncount= " << c << endl;
        if(c == 0)
        {
            //cout << "In here" << endl;
            newnode->next=NULL;
            FreeList->head = newnode;
            FreeList->printList();
            liveNodes -= 1;
            return 0;
        }
        Node* temp = FreeList->head;
        Node* prev = FreeList->head;
        //int c=FreeList->countList();
        liveNodes -= 1;
        while(addrs > temp->addr)
        { 	
            //cout << " \n addrs" << addrs << " temp-addr " << temp->addr;
	        prev=temp;
	        if(c > 1)
            {
                ////cout<< "h1\n"; 
                temp=temp->next;
            }
            else
            {
                break;
            }         
        }
        //cout << "\n HERE temp->addr " << temp->addr << " prev->addr " << prev->addr << "\n";
        if((prev->addr+prev->size) == addrs) 
        {   //cout <<" \n1";
	        prev->size += sizef;
	        if((prev->addr+prev->size) == temp->addr)
	        {
		        prev->size += temp->size;
		        prev->next=temp->next;
		        //free(temp);
	        }
        }
        else if((addrs+sizef) == temp->addr)
        {   //cout <<" \n3";
	        temp->size += sizef;
            temp->addr = addrs;
        }
        else
        {   //cout <<" \n4";
            if(prev->next == temp->next )
            {
                newnode->next=FreeList->head;
                FreeList->head=newnode;
            }
            else
            {
                newnode->next = prev->next;  
                prev->next = newnode;
            }         
        }
        FreeList->printList();
      //  cout << "-----------------------------------------------------------------------------------------";
        return 0;
    }
/*
	* Function Name: stats()
    * Parameters :  None
    * Return Type : void
    * Description : Prints the current stats after failure or success
    */
    void Heap::stats()
    {
        long int FreeSize=0,usedSize=0;
		long double used=0,avg=0;
		std::ofstream outfile;
        Node *findcount = FreeList->head;
        while(findcount != nullptr)
        {
            FreeSize += findcount->size;
            findcount=findcount->next;
        }
        long int c=FreeList->countList();
        //cout << "\n\nc=" << c;
        if(FreeList->countList() != 0)
        {
            usedSize = size - FreeSize;
        }
        else if (liveNodes > 0 and c==0)
        {
            usedSize=size;
            FreeSize=0;
            avg=0;
        }
        else
        {
            usedSize = 0;
            c=1;
            FreeSize=size;
        }
        //cout << " UsedSize= " << usedSize << " size= " << size << " FreeSize = " << FreeSize << "\n";  
        if(usedSize==0)
            used=0;   
        else
            used = (usedSize*100)/size;
        //cout << " used = " << used << endl; 
        //used = (usedSize/size)*100;
		//outfile.open ("stats.txt", std::ios::out | std::ios::app);
		cout << "\nheap_size = " << size ;
		cout << " live = " << liveNodes;
		cout << " used = " << used << "%" ;
		cout << " nodes = " << c;
        if (liveNodes > 0 and c==0)
        {
		    cout << " avg size = " << avg << std::endl ;
        }
        else
        {
            cout << " avg size = " << FreeSize/c << std::endl ;
        }
        
		//outfile.close();
		return;	
    }
