#include "parse.h"

class Parse
{
   public:
   bool save(const std::string filename, const std::string content)
   {
      /*
        save content to txt file
	  */
		ofstream file;
		if(file)
        {
		   file.open(filename.c_str());  
		   file << content;
		   file.close();
		   return true;
		} 
        else
        {
		   return false;
		}
   }
    
    std::string parse(const std::string content)
    {
    }
    std::string IntToStr(int x)
    {
       stringstream r;
       r << x;
       return r.str();
    } 
};
