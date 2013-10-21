#include "parse.cpp"
#include <map>
#include <fstream>
#include <vector>
#include <string>

string cmd, name, text;
int index, id, parentId; 
bool success = false;
//array to add node
map< int, map < string, string > > book;
map< int, map < string, string > > book2;
//init Parse object
Parse parse;
//filename to save current node state
string filename = "stream.txt";

class logic
{
   public:
   void add()
   {
        
      //add node to array
      while (!success)
      {
         cout << "Enter id and content: ";
         cin >> id >> name;
         if(cin.good())
         {
            int bCount = 0;
            bCount = book.size();
            
            book[bCount]["id"] = parse.IntToStr(id);
            book[bCount]["content"] = name;                       
            
            cout << "Created" << endl;
            cin.clear();
            printf("\nEnter command: ");
            break;
         } 
         else
         {
            cout << "Wrong input! Try again: \n";
            success = false;
            cin.clear();
            _flushall();
         }
      }
   }  
   
   void create()
   {
      //add node to array
	  while (!success)
      {
         cout << "Enter parent id, node id and content: ";
         cin >> parentId >> index >> text;
         if(cin.good())
         {
            int b2Count = 0;
            b2Count = book2.size();
            
            book2[b2Count]["parent"] = parse.IntToStr(parentId);
  			book2[b2Count]["id"] = parse.IntToStr(index);
            book2[b2Count]["content"] = text;
            
            cout << "Created" << endl;
            cin.clear();
            printf("\nEnter command: ");
            break;
         }
         else
         {
            cout << "Wrong input! Try again: \n";
            success = false;
            cin.clear();
            _flushall();
         }
      }     
   }   

   void load()
   {
      // get content node from file
      char* buff=NULL;
      int length;
      ifstream is;
      is.open ("stream.txt", ios::in );

      // get length of file:
      is.seekg (0, ios::end);
      length = is.tellg();
      is.seekg (0, ios::beg);
            
      buff = new char [length];
      // read data as a block:
      is.read (buff,length);
      is.close();
            
      cout.write (buff,length);
      delete[] buff;
      buff = NULL; 
            
      printf("\n \nEnter command: ");
   }
   
   void save()
   {
      int bCount = 0;
      int b2Count = 0;  
      bCount = book.size();              
      b2Count = book2.size();
            
	  //build node state
	  //save current node state to file
      
      string buildStringRelation("");
      for(int j = 0; j < bCount; j++)
      {
         buildStringRelation.append("\n");
	     buildStringRelation.append(" ");
         buildStringRelation.append(book[j]["id"]);
         buildStringRelation.append(" ");
         buildStringRelation.append(book[j]["content"]);
         
         for(int a = 0; a < b2Count; a++)
         {
            if(book[j]["id"] == book2[a]["parent"])
            {
    	       buildStringRelation.append("\n ");
               buildStringRelation.append(" ");
               buildStringRelation.append(book2[a]["id"]);
               buildStringRelation.append("  ");
               buildStringRelation.append(book2[a]["content"]);
               break;
            }
         }
      }         
      bool isSave = parse.save(filename, buildStringRelation);
      if(isSave)
      {
         cout << "Save was success!\n";
         printf("\nEnter command: ");
      }
      else
      {
         cout << "Save was not success!\n";
         printf("\nEnter command: ");
      }
   }
   
   void del()
   {
      //delete element from array
      cin >> id;
      int bCount = 0;
      int b2Count = 0; 
      bCount = book.size();    
      b2Count = book2.size();
                 
      for(int j = 0; j < bCount; j++)
      {
         if(book[j]["id"] == parse.IntToStr(id))
         {
            book.erase( j );
            for(int a = 0; a < b2Count; a++)
            {
               if(book2[a]["parent"] == parse.IntToStr(id))
               {
                  book2.erase( a );
                  break;    
               }
            }
            break;   
         }
      }
      cout << "Deleted" << endl;
      printf("\nEnter command: ");
   }
   
   void show()
   {
   	  //show tree of elements
      map< int, string >::const_iterator i;
      int b2Count = 0;
      int bCount = 0;
      bCount = book.size();
      b2Count = book2.size();
                  
      for(int j = 0; j < bCount; j++)
      {
         cout << book[j]["id"];
         cout << " " << book[j]["content"] << endl;
         for(int h = 0; h < b2Count; h++)
         {
            if(book[j]["id"] == book2[h]["parent"])
            {
               cout << "  " << book2[h]["id"];
               cout << " " << book2[h]["content"] << endl;  
            }
         }
      }
      printf("\nEnter command: "); 
   }
   
   void help()
   {
      printf("  add - create main node.\n");
      printf("  create_node - create node.\n");
      printf("  show - show all created node.\n");
      printf("  delete - delete main node.\n");
      printf("  save - saved books to the stream.txt .\n");
      printf("  load - show all saved nodes on a console.\n");
      printf("  quit - exit console.\n");
      printf("\nEnter command: ");
   }
};

int main()
{ 
	printf("Welcome to the TonySal test task. \n");
	printf("If you need help just put down command 'help'\n");
    printf("Enter command: ");
        
    logic logic1;
    	
    while( cin >> cmd ) 
    {
   	   if ( cmd == "add" ) 
       {
          logic1.add();		
       }
       else if ( cmd == "create_node" ) 
       {
	      logic1.create();
       } 
       else if ( cmd == "load" )
       {
          logic1.load();	
       }
       else if ( cmd == "save" )
       {
          logic1.save();     
       }
       else if ( cmd == "delete" )
       {
	      logic1.del();
   	   } 
       else if ( cmd == "show" )
       {
		  logic1.show();	 
       } 
       else if ( cmd == "help")
       {
          logic1.help();      
       } 
       else if ( cmd == "quit")
       {
	      //exit
          return 0;
       }
       else
       {
      	  cerr << "Bad command '" << cmd << "'" << endl;
          printf("\nEnter command: ");
       }   
    } // while( cin >> cmd )
 
    return 0;
} 
