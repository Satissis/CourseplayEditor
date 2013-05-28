#include "stdwx.h"

#include "AppFrame.h"

class CourseplayEditorApp : public wxApp
{
	virtual bool OnInit();

};

// Create the main functions for the application
IMPLEMENT_APP(CourseplayEditorApp);

bool CourseplayEditorApp::OnInit()
{
	wxString con = wxT("");
	AppFrame *frame = new AppFrame(wxT("Courseplay Editor - Version: ") + con + CP_EDITOR_VERSION , wxPoint(200, 200), wxSize(1000, 600));
	
	frame->Show(true);

	SetTopWindow(frame);

	return true;
}