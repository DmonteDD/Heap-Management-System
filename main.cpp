#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <bitset>
#include <math.h>
#include <map> 
#include <string>
#include <cstring>
#include "Heap.hpp"
#include "Object.hpp"
using namespace std;

int main(int argc, char *argv[])
{
	int alloc_addr,lineNo=0,lineNoArr=0;
	int threadid,objectid,classid,objectsize,objectref,parentid,childid,slotno,fmfield,fieldsize,fieldtype;
	std::string lines,ids;
	char a,b,c,d1,e,f,g;
    std::ifstream infile(argv[1]);
	std::ofstream outfile;

	if (argc == 4)
	{
		std::cout << " argv[1]= " <<argv[1];
		std::cout << " argv[2]= " <<argv[2];
		std::cout << " argv[3]= " <<argv[3] << std::endl;
	}
	else
	{
		std::cout << "\n Please enter correct number of arguments" << std::endl;
		std::cout << "\n------------------HELP------------------" << std::endl;
		std::cout << " Argument 1 : <Input Trace File Name> " << std::endl;
		std::cout << " Argument 2 : <Output File Name> " << std::endl;
		std::cout << " Argument 3 : <Heap Size> " << std::endl;
		std::cout << " Example : >./Heap trace.trace stats.txt 30" << std::endl; 
		return -1;
	}
	Heap H1(atoi(argv[3]));

	std::map<int,Object*> rootset;
	std::map<int,Object*> allocset; 
	std::map<int,Object*>::iterator itr; 
		
    if(!infile.is_open())
    {
	    std::cout<<" \n Error in opening file!!!"<< std::endl;
       	return 0;
   	}
	else
	{
		infile >> ids; 	
		while(!infile.eof())
		{
			if(ids == "c" || ids == "r" || ids == "s")
			{
				lineNo++;
			}

			if (ids == "a")
			{	
				lineNo++;
				infile >> a >> threadid >> b >> objectid >> c >> objectsize >> d1 >> objectref >> e >> classid;	
			
				alloc_addr=H1.allocate(objectsize);
				if(alloc_addr == -1)
				{
					freopen(argv[2],"a+",stdout);  
                	cout << "failed at line " << lineNo ;
                	H1.stats();					
					fclose(stdout);
    		   		exit(1);
				}
				Object* ob = new Object(threadid,objectid,objectsize,objectref,classid);
				allocset.emplace(objectid,ob);
				lineNoArr++;
			}

			if(ids== "+")
			{
				lineNo++;
				infile >> a >> threadid >> b >> objectid;	
				Object *temp = nullptr;
				itr = allocset.find(objectid); 
				if(itr == allocset.end()) 
       				 cout << "\n Not present in map" ; 
    			else
        		{
					//cout << "present : " << itr->first << "->" << itr->second ; 
					temp=itr->second;
					//cout << "\n Obj Size= " << temp->objectSize << "\n";
				}
				rootset.emplace(objectid,temp);
				/* cout << "\nThe map rootset is : "; 
			 	for (itr = rootset.begin(); itr != rootset.end(); ++itr) 
					{ 
						cout << "\t " << itr->first << "";
    				}   */
				//cout << "\nlineNo: " << lineNo;
			}
			if(ids == "e")
			{
				freopen(argv[2],"a+",stdout);  
            	cout << "Successful completion ";           
				H1.stats();
				fclose(stdout);
			}
				
			if(ids == "-")
			{
				lineNo++;
				infile >> a >> threadid >> b >> objectid;	
				rootset.erase(objectid);
   				//cout << "\nThe map rootset after deleting " << objectid << " is: "; 
   				//cout << "\t KEY \t ELEMENT\n"; 
				/* for (itr = rootset.begin(); itr != rootset.end(); ++itr) 
					{ 
						cout << "\t " << itr->first << "";
    				}   */
			} 
			infile >> ids;
			//cout << "next ids= " << ids << endl;
			if (ids == "w")
			{	
				lineNo++;
				infile >> a >> threadid >> b >> parentid >> c >> slotno >> d1 >> childid >> e >> fmfield >> f >> fieldsize >> g >> fieldtype;	
			    //cout <<  " \n " << threadid << " " << parentid << " " << slotno << " " << childid << " " << fmfield << " " << fieldsize << " " << fieldtype;	
				Object *temp = nullptr;
				itr = allocset.find(parentid); 
				if(itr == allocset.end()) 
       				 cout << "\n Not present in map" ; 
    			else
        		{
					//cout << "present : " << itr->first << "->" << itr->second ; 
					temp=itr->second;
					//cout << "\n Obj Size= " << temp->objectSize << "\n";
				}
				temp->objectRefSlots[slotno] =  childid;
				//cout << "\n Assigned: " << temp->objectRefSlots[slotno];
				

			}


			
		}	
		if(infile.eof())
		{
			freopen(argv[2],"a+",stdout);  
            cout << "Successful completion ";           
			H1.stats();
			fclose(stdout);
		}
	}
	outfile.close();
	return 0;

}