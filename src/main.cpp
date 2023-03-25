#include <iostream>
#include "DatabaseHandlers/DatabaseHandler.hh"


using namespace std;
using namespace pqxx;

int main(int argc, char *argv[])
{

  std::string sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (6, 'Paul', 32, 'California', 20000.00 ); ";
  DatabaseHandler::db_request(sql);

  
  //  try {
  //     connection C("dbname = test user = postgres password = 1953 \
  //     hostaddr = 127.0.0.1 port = 5432");
  //     if (C.is_open()) {
  //        cout << "Opened database successfully: " << C.dbname() << endl;
  //     } else {
  //        cout << "Can't open database" << endl;
  //        return 1;
  //     }
  //  } catch (const std::exception &e) {
  //     cerr << e.what() << std::endl;
  //     return 1;
  //  }

}