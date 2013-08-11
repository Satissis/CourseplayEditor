#include "Locale.h"
#include "Courseplay_EditorApp.h"
#include "Settings.h"

#include <wx/dir.h>
#include <wx/filename.h>


Locale::Locale(Settings *config)
{
    m_Config        = config;
	m_SearchPath    = wxPathOnly(wxGetApp().argv[0]);
	m_ConfigPath    = wxT("Locale");
	m_Locale        = NULL;

	selectedLangId  = wxLANGUAGE_UNKNOWN;
	shortLangName   = wxT("en");
}

Locale::~Locale()
{
    if(m_Locale)
	{
		wxDELETE(m_Locale);
	}
}

void Locale::getInstalledLanguages(LangList &langList, bool addDefault)
{
    langList.names.Clear();
    langList.fileNames.Clear();
	langList.identifiers.Clear();

	wxString filename;
	const wxLanguageInfo * langinfo;

	if (addDefault)
    {
        wxString name = wxLocale::GetLanguageName(wxLANGUAGE_DEFAULT);
        if(!name.IsEmpty())
        {
            langList.names.Add(_("Default"));
            langList.fileNames.Add(wxGetApp().GetAppName());
            langList.identifiers.Add(wxLANGUAGE_DEFAULT);
        }
    }

	if(!wxDir::Exists(m_SearchPath))
		return;

	wxDir dir(m_SearchPath);
	for(bool cont = dir.GetFirst(&filename,
#ifdef __WXMSW__
	wxT("*.*"),
#else
	wxT("*"),
#endif
	wxDIR_DEFAULT);
		cont; cont = dir.GetNext(&filename))
	{
        wxFileName tempFile(dir.GetName()+wxFileName::GetPathSeparator()+filename);
	    if (tempFile.GetExt() == wxT("mo") && tempFile.FileExists())
	    {
            langinfo = wxLocale::FindLanguageInfo(tempFile.GetName());
            if(langinfo != NULL)
            {
                langList.names.Add(langinfo->Description);
                langList.fileNames.Add(tempFile.GetName());
                langList.identifiers.Add(langinfo->Language);
            }
	    }
	}
}

bool Locale::askUserForLanguage(wxString msg, wxString caption)
{
    LangList langList;
    getInstalledLanguages(langList);

    if (langList.names.Count() == langList.identifiers.Count() && langList.fileNames.Count() == langList.identifiers.Count())
    {
        long index = wxGetSingleChoiceIndex(msg, caption, langList.names);
        if(index != -1)
        {
            if(m_Locale)
            {
                wxDELETE(m_Locale);
            }
            m_Locale = new wxLocale;
            m_Locale->Init(langList.identifiers[index]);
            m_Locale->AddCatalogLookupPathPrefix(m_SearchPath);
            m_Locale->AddCatalog(langList.fileNames[index]);

            selectedLangId = langList.identifiers[index];

            return true;
        }
    }

	return false;
}

bool Locale::loadLocale()
{
	long language;

	wxString regString = wxString::Format(wxT("/%s/Language"), m_ConfigPath.c_str());
	if(!m_Config->Read(regString, &language, wxLANGUAGE_UNKNOWN))
	{
		language = wxLANGUAGE_UNKNOWN;
	}

	if(language == wxLANGUAGE_UNKNOWN)
	{
		return false;
	}

	LangList langList;
	getInstalledLanguages(langList);

	for(size_t i = 0; i < langList.identifiers.Count(); i++)
	{
		if(langList.identifiers[i] == language)
		{
			if(m_Locale) wxDELETE(m_Locale);
			m_Locale = new wxLocale;
			m_Locale->Init(langList.identifiers[i]);
			m_Locale->AddCatalogLookupPathPrefix(m_SearchPath);
			m_Locale->AddCatalog(langList.fileNames[i]);

			shortLangName = langList.fileNames[i];

			selectedLangId = langList.identifiers[i];

			return true;
		}
	}
	return false;
}

bool Locale::loadDefaultLocaleIfExists()
{
    LangList langList;
	getInstalledLanguages(langList);

	long defaultLangID = wxLocale::GetSystemLanguage();

    if (defaultLangID != wxLANGUAGE_UNKNOWN)
    {
        for(size_t i = 0; i < langList.identifiers.Count(); i++)
        {
            if(langList.identifiers[i] == defaultLangID)
            {
                if(m_Locale) wxDELETE(m_Locale);
                m_Locale = new wxLocale;
                m_Locale->Init(langList.identifiers[i]);
                m_Locale->AddCatalogLookupPathPrefix(m_SearchPath);
                m_Locale->AddCatalog(langList.fileNames[i]);

                shortLangName = langList.fileNames[i];

                selectedLangId = langList.identifiers[i];

                return true;
            }
        }
    }
	return false;
}

void Locale::saveLocale(bool bReset)
{
	long language = wxLANGUAGE_UNKNOWN;
	if(!bReset)
	{
		if(m_Locale)
		{
			language = m_Locale->GetLanguage();
		}
	}

	wxString regString = wxString::Format(wxT("/%s/Language"), m_ConfigPath.c_str());
	m_Config->Write(regString, language);
	m_Config->Flush();

}

void Locale::setLocaleSearchPath(wxString langPath)
{
	if(langPath.IsEmpty())
        m_SearchPath = wxPathOnly(wxGetApp().argv[0]);
	else
    {
        wxFileName appFileName(wxGetApp().argv[0]);
        appFileName.Normalize(wxPATH_NORM_DOTS|wxPATH_NORM_ABSOLUTE|wxPATH_NORM_TILDE);

        m_SearchPath = appFileName.GetPath() + appFileName.GetPathSeparator() + langPath;
    }
}

void Locale::setLocaleConfigPath(wxString value)
{
    if (!value.IsEmpty())
        m_ConfigPath = value;
}

void Locale::setSelectedLangId(wxLanguage lang)
{
    selectedLangId = lang;
    wxString regString = wxString::Format(wxT("/%s/Language"), m_ConfigPath.c_str());
	m_Config->Write(regString, selectedLangId);
}
