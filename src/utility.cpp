#include "utility.h"

bool FileExist( const std::string& Name)
{
  return boost::filesystem::exists(Name); 
}
