#include "config.h"

#include <execution>

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

		std::string value;
		bool is_quoted_str = false;

		size_t str_start_pos = line.find('\"');
		if (str_start_pos != std::string::npos)
		{
			size_t str_end_pos = line.find('\"', str_start_pos + 1);
			if (str_end_pos == std::string::npos)
			{
				Error("Could not parse string", line_num);
				continue;
			}

			size_t token_length = str_end_pos - str_start_pos;

			value = line.substr(str_start_pos + 1, token_length - 1);
			line.erase(line.begin() + str_start_pos, line.begin() + str_end_pos + 1);

			is_quoted_str = true;
		}

		line.erase(std::remove_if(line.begin(), line.end(), std::isspace), line.end());

		size_t assign_pos = line.find('=');
		if (assign_pos == std::string::npos)
		{
			Error("Could not parse token identifier '" + line + "'", line_num);
			continue;
		}

		if (str_start_pos <= assign_pos)
		{
			Error("Could not parse invalid token identifier '" + value + "'", line_num);
			continue;
		}

		std::string identifier = line.substr(0, assign_pos);

		if (!is_quoted_str)
			value = line.substr(assign_pos + 1, line.length() - assign_pos - 1);

		if (value.empty())
		{
			Warn("Empty token '" + identifier + "'. This may cause undefined behaviour", line_num);
		}

		if (!in_section)
		{
			Error("Token '" + identifier + "' missing section header", line_num);
			continue;
		}

		config[section][identifier] = value;
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

bool Config::HasErrors()
{
	return !errors.empty();
}

const std::vector<std::string> Config::GetErrors()
{
	return errors;
}
