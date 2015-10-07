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
	void Load(Identifier id, const std::string& filename);
	template<typename Parameter>
	void Load(Identifier id, const std::string& filename, const Parameter& par);
	Resource& get(Identifier id);
	const Resource&	get(Identifier id) const;

	private:
	std::map<Identifier, std::unique_ptr<Resource>> resourceMap_;
};

//#include "resourcemanager.inl"
