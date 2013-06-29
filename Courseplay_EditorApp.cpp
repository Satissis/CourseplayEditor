/***************************************************************
 * Name:      Courseplay_EditorApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Claus G. Pedersen aka Satis (satissis@gmail.com)
 * Created:   2013-06-08
 * Copyright: Claus G. Pedersen aka Satis (https://github.com/Satissis/CourseplayEditor)
 * License:
 **************************************************************/

#include "Courseplay_EditorApp.h"
#include <wx/filename.h>

#ifdef __WXDEBUGLOG__
    #include <wx/log.h>
#endif

#include "Settings.h"

//(*AppHeaders
#include "Courseplay_EditorMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(Courseplay_EditorApp);

bool Courseplay_EditorApp::OnInit()
{
#ifdef __WXDEBUGLOG__
    logWindow = new wxLogWindow(NULL, wxT("Debug Logging"));
    wxLog::SetActiveTarget(logWindow);
#endif

    SetAppName(wxT("Courseplay Editor"));

	Settings *setup = new Settings();

	if (setup->isFirstTimeSetup())
        setup->doFirstTimeSetup();
    else
        setup->loadLocale();

    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	Courseplay_EditorFrame* Frame = new Courseplay_EditorFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)

    delete setup;

    return wxsOK;
}
