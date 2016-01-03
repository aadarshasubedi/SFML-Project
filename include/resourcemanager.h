#pragma once

#include <cassert>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

#include <SFML/Graphics.hpp>

template <typename Resource, typename Identifier>
class ResourceManager
{
	public:
	template<typename Parameter>
	void			Load(Identifier id, const std::string& filename, const Parameter& par)
	{
		std::unique_ptr<Resource> resource(new Resource());
		if (!resource->loadFromFile(filename, par))
		{
			throw std::runtime_error("ResourceManager::Load() - Failed to load " + filename + " " rhs);
		}

		auto inserted = resources_.insert(std::make_pair(id, std::move(resource)));
		assert(inserted.second);
	}
	void			Load(Identifier id, const std::string& filename)
	{
		std::unique_ptr<Resource> resource(new Resource());
		if (!resource->loadFromFile(filename))
		{
			throw std::runtime_error("ResourceManager::Load() - Failed to load " + filename);
		}

		auto inserted = resources_.insert(std::make_pair(id, std::move(resource)));
		assert(inserted.second);
	}
	Resource&		get(Identifier id)
	{
		auto found = resources_.find(id);
		assert(found != resources_.end());
		return *(found)->second;
	}
	const Resource&	get(Identifier id) const
	{
		auto found = resources_.find(id);
		assert(found != resources_.end());
		return *(found)->second;
	}

	private:
	std::map<Identifier, std::unique_ptr<Resource>> resources_;
};
