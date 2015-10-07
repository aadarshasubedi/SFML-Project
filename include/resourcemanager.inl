#include "resourcemanager.h"

// create a 'resource' and load the 'resource file' associated with it
// insert the new 'resource' with its 'id' in the 'resourceMap_' and check for success
template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::Load(Identifier id, const std::string& filename)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
	{
		throw std::runtime_error("ResourceManager::Load() - Failed to load " + filename);
	}

	auto inserted = resourceMap_.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

// create a 'resource' and load the 'resource file' associated with it
// insert the new 'resource' with its 'id' in the 'resourceMap_' and check for success
// 'loadFromFile' can take 2 arguments when dealer with shaders
template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceManager<Resource, Identifier>::Load(Identifier id, const std::string& filename, const Parameter& par)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename, par))
	{
		throw std::runtime_error("ResourceManager::Load() - Failed to load " + filename + " " rhs);
	}

	auto inserted = resourceMap_.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

// search for 'resource' by 'id' in the 'resourceMap_' and return 'esource' if found
template <typename Resource, typename Identifier>
Resource& ResourceManager<Resource, Identifier>::get(Identifier id)
{
	auto found = resourceMap_.find(id);
	assert(found != resourceMap_.end());
	return *(found)->second;
}

// search for 'resource' by 'id' in the 'resourceMap_' and return 'resource' if found
// const qualifier for const 'resource'
template <typename Resource, typename Identifier>
const Resource& ResourceManager<Resource, Identifier>::get(Identifier id) const
{
	auto found = resourceMap_.find(id);
	assert(found != resourceMap_.end());
	return *(found)->second;
}
