#ifndef LOCALE_H_INCLUDED
#define LOCALE_H_INCLUDED

#include <wx/wx.h>
#include <wx/intl.h>
#include "Variables.h"

class Settings;

class Locale
{
public: // Functions
    Locale(Settings *config);
    ~Locale();

    void getInstalledLanguages(LangList &langList, bool addDefault = false);
	bool askUserForLanguage(wxString msg, wxString caption);
	bool loadLocale();
	bool loadDefaultLocaleIfExists();
	void saveLocale(bool bReset = false);

	void setLocaleSearchPath(wxString value);
	void setLocaleConfigPath(wxString value);

	virtual void setSelectedLangId(wxLanguage lang);

public: // Variables
    long selectedLangId;
    wxString shortLangName;

private: // Variables
    Settings *m_Config;
	wxString  m_SearchPath;
	wxString  m_ConfigPath;
	wxLocale *m_Locale;
};

#endif // LOCALE_H_INCLUDED
