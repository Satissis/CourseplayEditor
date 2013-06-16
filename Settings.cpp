#include "Settings.h"

Settings::Settings(wxFrame *frame, const wxString& appName)
        : wxConfig(appName)
{
    parent = frame;
}

Settings::~Settings()
{
    // Here for destructing things if needed.
}
