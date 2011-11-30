#include "Precompiled.h"
#include "Database.h"

template<> Database *Singleton<Database>::mSingleton = NULL;

Database::Database(const std::string &fileName)
: mConnection(fileName)
{
}

void Database::execQuery(const std::string &text)
{
	CL_DBCommand command = mConnection.create_command(text);
	mReader = mConnection.execute_reader(command);
}

bool Database::nextRow()
{
	return mReader.retrieve_row();
}

std::string Database::getString(const std::string &column)
{
	return mReader.get_column_string(column);
}

int Database::getInt(const std::string &column)
{
	return mReader.get_column_int(column);
}

double Database::getFloat(const std::string &column)
{
	return mReader.get_column_double(column);
}

void Database::closeQuery()
{
	mReader.close();
}
