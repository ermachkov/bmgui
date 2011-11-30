#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "Singleton.h"

class Resource;

// Class for managing various game resources (sprites, fonts, sounds etc.)
class ResourceManager : public Singleton<ResourceManager>
{
public:

	// Creates a resource object
	CL_SharedPtr<Resource> createResource(const std::string &name, const std::string &fileName);

	// Creates all resources from the specified resource file
	std::vector<CL_SharedPtr<Resource> > createAllResources(const std::string &fileName);

	// Returns a resource object
	CL_SharedPtr<Resource> getResource(const std::string &name) const;

	// Loads a resource from the specified resource file
	void loadResource(const std::string &name, const std::string &fileName);

	// Loads all resources from the specified resource file
	void loadAllResources(const std::string &fileName);

	// Unloads the resource
	void unloadResource(const std::string &name);

	// Unloads all resources declared in the specified resource file
	void unloadAllResources(const std::string &fileName);

private:

	// Name -> Resource map type
	typedef std::map<std::string, CL_SharedPtr<Resource> > ResourceMap;

	// Filename -> Resource File map type
	typedef std::map<std::string, CL_ResourceManager> ResourceFileMap;

	// Loads a resource file
	CL_ResourceManager loadResourceFile(const std::string &fileName);

	ResourceMap         mResources;         // List of the resource objects
	ResourceFileMap     mResourceFiles;     // List of the resource files
};

#endif
