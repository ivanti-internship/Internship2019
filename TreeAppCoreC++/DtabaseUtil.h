#pragma once
#include<string> 
#include "sqlite3.h"

using namespace std;

class DtabaseUtil
{
public:
	DtabaseUtil();
	~DtabaseUtil();
	static void ExecuteNonQuery(string queryString, sqlite3 * databseConnection);
	static sqlite3* openDatabaseConnection(string dabaseName);
	static void closeDatabseConnection(sqlite3 * databseConnection);
};

