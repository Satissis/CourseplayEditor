#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#include <wx/wx.h>
#include <wx/config.h>

class Settings : public wxConfig
{
public:
    Settings(wxFrame *frame, const wxString& appName = wxEmptyString);
    virtual ~Settings();

protected:
    wxFrame *parent;
};


#endif // SETTINGS_H_INCLUDED
