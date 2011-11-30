#ifndef RESOURCE_H
#define RESOURCE_H

// Base resource class
class Resource
{
public:

	// Destructor
	virtual ~Resource()
	{
	}

	// Returns a list of resource dependencies
	virtual std::vector<std::string> getDependencies() const = 0;

	// Returns a list of resource filenames
	virtual std::vector<std::string> getFileNames() const = 0;

	// Returns true if the resource is loaded
	virtual bool isLoaded() const = 0;

	// Loads the resource
	virtual void load() = 0;

	// Loads data file in the background thread
	virtual void loadInBackgroundThread(const std::string &fileName, CL_SharedPtr<Resource> &firstResource) = 0;

	// Loads data file in the main thread
	virtual void loadInMainThread(const std::string &fileName, CL_SharedPtr<Resource> &firstResource) = 0;
};

#endif
