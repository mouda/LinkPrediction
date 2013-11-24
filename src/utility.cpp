#include "utility.h"
#include <limits>

bool FileExist( const std::string& Name)
{
  return boost::filesystem::exists(Name); 
}

std::istream& Ignoreline(std::ifstream& in, std::ifstream::pos_type& pos)
{
  pos = in.tellg();
  return in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string GetLastLine(std::ifstream& in)
{
  std::ifstream::pos_type pos = in.tellg();

  std::ifstream::pos_type lastPos;
  while (in >> std::ws && Ignoreline(in, lastPos))
    pos = lastPos;

  in.clear();
  in.seekg(pos);

  std::string line;
  std::getline(in, line);
  in.clear();
  in.seekg(std::ios::beg);
  return line;
}
