#include "DtabaseUtil.h"
#include<iostream>

using namespace std;

struct sqlite3_deleter {
	void operator()(sqlite3* sql) {
		sqlite3_close_v2(sql);
	}
};


DtabaseUtil::DtabaseUtil()
{
}


DtabaseUtil::~DtabaseUtil()
{
}


void DtabaseUtil::ExecuteNonQuery(string queryString, sqlite3 *databseConnection)
{

	char* messaggeError;

	int exit = sqlite3_exec(databseConnection, queryString.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error Insert" << std::endl;
		sqlite3_free(messaggeError);
	}
	else {
		std::cout << "Records created Successfully!" << std::endl;
	}
		
}

sqlite3* DtabaseUtil::openDatabaseConnection(string dabaseName)
{
	sqlite3* DB;
	int exit = sqlite3_open(dabaseName.c_str(), &DB);
	// delete(DB);
	return  DB;
}


void DtabaseUtil::closeDatabseConnection(sqlite3* databseConnection)
{
	sqlite3_close(databseConnection);
}

void DtabaseUtil::ExecuteQuery(string queryString, sqlite3 *databaseConnection, sqlite3_callback callback) {
	char* messageError;

	int exit = sqlite3_exec(databaseConnection, queryString.c_str(), callback, NULL, &messageError);

	if (exit != SQLITE_OK) {
		std::cerr << "Error Query" << std::endl;
		std::cerr << messageError << std::endl;
		sqlite3_free(messageError);
	} else {
		std::cout << "Read successfull" << std::endl;
	}
}





