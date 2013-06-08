/***************************************************************
 * Name:      Courseplay_EditorApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Claus G. Pedersen aka Satis (satissis@gmail.com)
 * Created:   2013-06-08
 * Copyright: Claus G. Pedersen aka Satis (https://github.com/Satissis/CourseplayEditor)
 * License:
 **************************************************************/

#include "Courseplay_EditorApp.h"

//(*AppHeaders
#include "Courseplay_EditorMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(Courseplay_EditorApp);

bool Courseplay_EditorApp::OnInit()
{
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
    return wxsOK;

}
