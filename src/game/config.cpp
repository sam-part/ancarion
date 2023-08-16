#include "config.h"

#include <fstream>
#include <iostream>

void Config::Error(const std::string& message)
{
	errors.push_back(message);
	std::cout << message << "\n";
}

void Config::Error(const std::string& message, size_t line)
{
	std::string error_message = "CONFIG_ERROR: " + message + " (Line " + std::to_string(line) + ")";
	Error(error_message);
}

void Config::Warn(const std::string& message)
{
	std::cout << message << "\n";
}

void Config::Warn(const std::string& message, size_t line)
{
	std::cout << "CONFIG_WARN: " << message << " (Line " << line << ")\n";
}

std::string RemoveWhitespace(const std::string& string, size_t start_pos, size_t end_pos)
{
	size_t first_char_pos = string.find_first_not_of(' ', start_pos);

	if (first_char_pos == std::string::npos)
		return "";

	size_t length = end_pos - (first_char_pos - start_pos);

	std::string str = string.substr(first_char_pos, length);

	// Remove whitespace on string end
	for (size_t idx = str.length(); idx-- > 0; )
		if (!isspace(str[idx]))
			return str.substr(0, idx + 1);
}

Config::Config(const std::string& path)
{
	std::ifstream file(path);

	if (!file)
	{
		Error("Could not open file " + path);
		return;
	}

	std::string line;
	std::string section;
	size_t line_num = 0;
	bool in_section = false;

	while (std::getline(file, line))
	{
		line_num++;

		if (line.empty())
			continue;

		size_t first_char_pos = line.find_first_not_of(' ');

		if (first_char_pos == std::string::npos || line[first_char_pos] == comment_token)
			continue;

		if (line[first_char_pos] == '[')
		{
			size_t section_end_pos = line.find(']');
			if (section_end_pos == std::string::npos)
			{
				Error("Could not parse section header '" + line + "'", line_num);
				continue;
			}

			section = line.substr(first_char_pos + 1, section_end_pos - first_char_pos - 1);
			in_section = true;

			continue;
		}

		size_t assign_pos = line.find_first_of('=', first_char_pos);

		if (assign_pos == std::string::npos)
		{
			Error("Could not parse token identifier '" + line + "'", line_num);
			continue;
		}

		std::string identifier = RemoveWhitespace(line, first_char_pos, assign_pos - first_char_pos);
		std::string raw_value = RemoveWhitespace(line, assign_pos + 1, line.length());

		if (!in_section)
		{
			Error("Token '" + identifier + "' missing section header", line_num);
			continue;
		}

		if (raw_value.empty())
		{
			Warn("Empty token '" + identifier + "'. This may cause undefined behaviour", line_num);
			config[section][identifier] = "";
			continue;
		}

		if (raw_value[0] == '{') // List
		{
			std::vector<std::string> values;

			size_t search_pos = 1;
			while (true)
			{
				size_t end_pos = raw_value.find_first_of(',', search_pos);

				if (end_pos == std::string::npos)
					end_pos = raw_value.find_first_of('}', search_pos);

				if (end_pos == std::string::npos)
					break;

				values.push_back(RemoveWhitespace(raw_value, search_pos, end_pos - search_pos));

				search_pos = end_pos + 1;
			}

			list_config[section][identifier] = values;
		}
		else
		{
			config[section][identifier] = raw_value;
		}
	}
}

std::string Config::GetString(const std::string& section, const std::string& identifier)
{
	auto it = config[section].find(identifier);
	if (it != config[section].end())
		return it->second;

	Warn("Token '" + identifier + "' in section [" + section + "] does not exist");

	return {};
}

bool Config::IsList(const std::string& section, const std::string& identifier)
{
	return list_config[section].contains(identifier);
}

std::vector<std::string> Config::GetList(const std::string& section, const std::string& identifier)
{
	auto it = list_config[section].find(identifier);
	if (it != list_config[section].end())
		return it->second;

	Warn("List '" + identifier + "' in section [" + section + "] does not exist");

	return {};
}

bool Config::HasErrors()
{
	return !errors.empty();
}

const std::vector<std::string> Config::GetErrors()
{
	return errors;
}
