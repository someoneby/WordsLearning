#include <iostream>
#include <locale.h>

#include "DatabaseHandlers/DatabaseHandler.hh"

using namespace std;
using namespace pqxx;


// select ew."Word" as word, rw."Word" as translate from public."EnglishWords" ew 
// 	join public."EnglishToRussian" etr on ew.id="EnglishWordId" 
// 	join public."RussianWords" rw on etr."RussianWordId"=rw."id"
// 	where ew."Topic" in ('animal', 'it');


int main(int argc, char *argv[])
{
  setlocale(LC_ALL, "ru_RU.UTF-8");

  std::set<std::string> topics {"animal"};

  DatabaseHandler::db_select(english, russian, topics);

  std::cout << "\n\nRU to ENG\n\n";

  DatabaseHandler::db_select(russian, english, topics);
}