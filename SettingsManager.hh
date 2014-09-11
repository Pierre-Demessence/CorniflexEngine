#ifndef			SETTINGSMANAGER_H_
# define		SETTINGSMANAGER_H_

# include		<list>
# include		<map>
# include		<string>

class			SettingsManager
{
protected:
  std::string		filename;
  std::map<std::string, std::string>	params;
  std::map<std::string, std::string>	paramsDefault;

public:
  SettingsManager(std::string);
  SettingsManager(const SettingsManager&);
  ~SettingsManager();
  SettingsManager&	operator=(const SettingsManager&);

  bool			exist(const std::string &key) const;
  bool			check(const std::string &key, const std::string &value) const;
  const std::map<std::string, std::string>	&getParams() const;

  void			set(const std::string &key, const std::string &value);
  void			erase(const std::string &key);

};

#endif			/* !SETTINGSMANAGER_H_ */
