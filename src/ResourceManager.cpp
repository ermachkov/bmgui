#include "Precompiled.h"
#include "ResourceManager.h"
#include "Application.h"
#include "FontResource.h"
#include "SoundResource.h"
#include "SpriteResource.h"

template<> ResourceManager *Singleton<ResourceManager>::mSingleton = NULL;

CL_SharedPtr<Resource> ResourceManager::createResource(const std::string &name, const std::string &fileName)
{
	ResourceMap::const_iterator it = mResources.find(name);
	if (it != mResources.end())
		return it->second;

	CL_ResourceManager resourceManager = loadResourceFile(fileName);
	CL_Resource resource = resourceManager.get_resource(name);

	CL_SharedPtr<Resource> ptr;
	std::string type = resource.get_type();
	if (type == "font")
		ptr = CL_SharedPtr<Resource>(new FontResource(resource));
	else if (type == "sprite")
		ptr = CL_SharedPtr<Resource>(new SpriteResource(resource));
	else if (type == "sample")
		ptr = CL_SharedPtr<Resource>(new SoundResource(resource));
	else
		throw Exception(cl_format("Resource '%1' has invalid or unsupported type '%2'", name, type));

	mResources.insert(std::make_pair(name, ptr));
	return ptr;
}

std::vector<CL_SharedPtr<Resource> > ResourceManager::createAllResources(const std::string &fileName)
{
	CL_ResourceManager resourceManager = loadResourceFile(fileName);
	std::vector<CL_String> names = resourceManager.get_resource_names();
	std::vector<CL_SharedPtr<Resource> > resources;
	for (std::vector<CL_String>::const_iterator it = names.begin(); it != names.end(); ++it)
		resources.push_back(createResource(*it, fileName));
	return resources;
}

CL_SharedPtr<Resource> ResourceManager::getResource(const std::string &name) const
{
	ResourceMap::const_iterator it = mResources.find(name);
	if (it == mResources.end())
		throw Exception("Resource '" + name + "' is not found");
	return it->second;
}

void ResourceManager::loadResource(const std::string &name, const std::string &fileName)
{
	CL_SharedPtr<Resource> resource = createResource(name, fileName);

	std::vector<std::string> dependencies = resource->getDependencies();
	for (std::vector<std::string>::const_iterator it = dependencies.begin(); it != dependencies.end(); ++it)
		loadResource(*it, fileName);

	resource->load();
}

void ResourceManager::loadAllResources(const std::string &fileName)
{
	CL_ResourceManager resourceManager = loadResourceFile(fileName);
	std::vector<CL_String> names = resourceManager.get_resource_names();
	for (std::vector<CL_String>::const_iterator it = names.begin(); it != names.end(); ++it)
		loadResource(*it, fileName);
}

void ResourceManager::unloadResource(const std::string &name)
{
	mResources.erase(name);
}

void ResourceManager::unloadAllResources(const std::string &fileName)
{
	CL_ResourceManager resourceManager = loadResourceFile(fileName);
	std::vector<CL_String> names = resourceManager.get_resource_names();
	for (std::vector<CL_String>::const_iterator it = names.begin(); it != names.end(); ++it)
		unloadResource(*it);
	mResourceFiles.erase(fileName);
}

CL_ResourceManager ResourceManager::loadResourceFile(const std::string &fileName)
{
	ResourceFileMap::const_iterator it = mResourceFiles.find(fileName);
	if (it != mResourceFiles.end())
		return it->second;

	CL_ResourceManager resourceManager(Application::getSingleton().getDataDirectory() + fileName);
	mResourceFiles.insert(std::make_pair(fileName, resourceManager));
	return resourceManager;
}
