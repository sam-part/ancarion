#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>

class Config
{
private:
	char comment_token = '#';

	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> config;
	std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> list_config;

	std::vector<std::string> errors;

	void Error(const std::string& message);
	void Error(const std::string& message, size_t line);
	void Warn(const std::string& message);
	void Warn(const std::string& message, size_t line);

public:
	Config(const std::string& path);

	std::string GetString(const std::string& section, const std::string& identifier);

	template<typename T>
	T Get(const std::string& section, const std::string& identifier);

	bool IsList(const std::string& section, const std::string& identifier);
	std::vector<std::string> GetList(const std::string& section, const std::string& identifier);

	bool HasErrors();
	const std::vector<std::string> GetErrors();
};

template<typename T>
inline T Config::Get(const std::string& section, const std::string& identifier)
{
	static_assert(not std::same_as<T, std::string>, "Must be non-string type");

	std::string str_value = GetString(section, identifier);
	std::istringstream iss(str_value);

	T t_value{};
	iss >> t_value;

	return t_value;
}