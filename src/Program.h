#ifndef PROGRAM_H
#define PROGRAM_H

// Program class
class Program
{
public:

	// Program main function
	static int main(const std::vector<CL_String> &args);

private:

	// ClanLib global application object
	static CL_ClanApplication mApplication;
};

#endif
