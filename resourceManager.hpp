#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"

using namespace nlohmann;

template<typename Derived, typename T>
class ResourceManager {
public:
	ResourceManager(const std::vector<std::string> &l_pathsFiles) {
		LoadPaths(l_pathsFiles);
	}

	virtual ~ResourceManager() {
		PurgeResources();
	}

	T* GetResource(const std::string& l_id) {
		auto res = Find(l_id);
		return(res ? res->first : nullptr);
	}

	std::string GetPath(const std::string &l_id) {
		auto path = m_paths.find(l_id);
		return(path != m_paths.end() ? path->second : "");
	}

	bool RequireResource(const std::string &l_id) {
		auto res = Find(l_id);
		if (res) {
			++res->second;
			return true;
		}
		auto path = m_paths.find(l_id);
		if (path == m_paths.end()) { return false; }
		T* resource = Load(path->second);
		if (!resource) { return false; }
		m_resources.emplace(l_id, std::make_pair(resource, 1));
		return true;
	}

	bool ReleaseResource(const std::string &l_id) {
		auto res = Find(l_id);
		if (!res) { return false; }
		--res->second;
		if (!res->second) { Unload(l_id); }
		return true;
	}

	void PurgeResources() {
		while (m_resources.begin() != m_resources.end()) {
			delete m_resources.begin()->second.first;
			m_resources.erase(m_resources.begin());
		}
	}

	T* Load(const std::string &l_path) {
		return static_cast<Derived*>(this)->Load(l_path);
	}

	unsigned int getSize() {
		return m_resources.size();
	}

private:
	//											  Telt hoe vaak wordt resource gebruikt
	std::unordered_map<std::string, std::pair<T*, unsigned int>> m_resources;
	std::unordered_map<std::string, std::string> m_paths;

	std::pair<T*, unsigned int>* Find(const std::string &l_id) {
		auto itr = m_resources.find(l_id);
		return (itr != m_resources.end() ? &itr->second : nullptr);
	}

	bool Unload(const std::string &l_id) {
		auto itr = m_resources.find(l_id);
		if (itr == m_resources.end()) { return false; }
		delete itr->second.first;
		m_resources.erase(itr);
		return true;

	}

	//Added vector of strings. All type "grid"-json files in this vector
	void LoadPaths(const std::vector<std::string> &l_pathFiles) {
		for (auto &i : l_pathFiles) {
			std::ifstream paths;
			paths.open(i);
			json j;
			paths >> j;
			json::array_t pathArray = j["data"]["grid"]["tileset"];
			unsigned int arraySize = pathArray.size();
			if (paths.is_open()) {
				for (unsigned i = 0; i < arraySize; i++) {
					std::string tmp = pathArray[i];
					m_paths.emplace(std::to_string(i), tmp);
				}
				paths.close();
			}
			else {
				std::cerr <<
					"! Failed loading JSON file: "
					<< i << std::endl;
			}
		}
		
	}
};

#endif // RESOURCE_MANAGER_HPP