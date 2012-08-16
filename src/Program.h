#ifndef PROGRAM_H
#define PROGRAM_H

// Program class
class Program
{
public:

	// Program main function
	static int main(const std::vector<CL_String> &args);

	// Quotify utility function for error handling
	static std::string quotify(const std::string &text);

private:

	// ClanLib global application object
	static CL_ClanApplication mApplication;
};

#endif
