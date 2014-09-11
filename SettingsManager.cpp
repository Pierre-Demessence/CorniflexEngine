#include <algorithm>
#include <fstream>
#include <iostream>

#include "SettingsManager.hh"

//----- ----- Constructors ----- ----- //
SettingsManager::SettingsManager(std::string filename)
{
  std::fstream		file;

  this->filename = filename;
  this->paramsDefault["DEFAULT"] = "42";

  file.open(this->filename, std::fstream::in);
  if (file.good())
    {
      std::string line;
      while (getline(file, line))
	{
	  line = line.substr(0, line.find('#'));
	  if (line.empty())
	    continue;
	  std::string key;
	  std::string value;

	  key = line.substr(0, line.find('='));
	  value = line.substr(line.find('=')+1);
	  if (!key.empty())
	    this->params[key] = value;
	}
    }
  file.close();
  
  file.open(this->filename, std::fstream::out | std::fstream::app);
  std::for_each(this->paramsDefault.begin(), this->paramsDefault.end(), [this, &file] (const std::pair<std::string, std::string> &param) {
      if (this->params.find(param.first) == this->params.end())
  	file << std::endl << param.first << "=" << param.second << std::endl;
    });
  file.close();
}

SettingsManager::SettingsManager(const SettingsManager& ref)
{
  this->filename = filename;
  std::for_each(ref.params.begin(), ref.params.end(), [this] (const std::pair<std::string, std::string> &param) {
      this->params[param.first] = param.second;
    });
}

//----- ----- Destructor ----- ----- //
SettingsManager::~SettingsManager()
{}

//----- ----- Operators ----- ----- //
SettingsManager&	SettingsManager::operator=(const SettingsManager& ref)
{
  this->filename = filename;
  std::for_each(ref.params.begin(), ref.params.end(), [this] (const std::pair<std::string, std::string> &param) {
      this->params[param.first] = param.second;
    });
  return (*this);
}

//----- ----- Getters ----- ----- //
bool	SettingsManager::exist(const std::string &key) const
{
  return (this->params.find(key) != this->params.end());
}

bool	SettingsManager::check(const std::string &key, const std::string &value) const
{
  return (this->exist(key) && this->params.at(key) == value);
}

const std::map<std::string, std::string>	&SettingsManager::getParams() const
{
  return (this->params);
}

//----- ----- Setters ----- ----- //
void	SettingsManager::set(const std::string &key, const std::string &value)
{
  this->params[key] = value;
}

void	SettingsManager::erase(const std::string &key)
{
  this->params.erase(key);
}
