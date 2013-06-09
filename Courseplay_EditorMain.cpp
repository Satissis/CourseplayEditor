/***************************************************************
 * Name:      Courseplay_EditorMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Claus G. Pedersen aka Satis (satissis@gmail.com)
 * Created:   2013-06-08
 * Copyright: Claus G. Pedersen aka Satis (https://github.com/Satissis/CourseplayEditor)
 * License:
 **************************************************************/

#include "Courseplay_EditorMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(Courseplay_EditorFrame)
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

#include "wxPNGResource.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(Courseplay_EditorFrame)
const long Courseplay_EditorFrame::ID_TLB1_BTN_NEW = wxNewId();
const long Courseplay_EditorFrame::ID_BUTTON1 = wxNewId();
const long Courseplay_EditorFrame::TLB_1 = wxNewId();
const long Courseplay_EditorFrame::ID_Main_Window = wxNewId();
const long Courseplay_EditorFrame::ID_COURSELIST = wxNewId();
const long Courseplay_EditorFrame::ID_BUTTON2 = wxNewId();
const long Courseplay_EditorFrame::ID_BUTTON3 = wxNewId();
const long Courseplay_EditorFrame::ID_BUTTON4 = wxNewId();
const long Courseplay_EditorFrame::ID_PANEL1 = wxNewId();
const long Courseplay_EditorFrame::ID_File_Load = wxNewId();
const long Courseplay_EditorFrame::ID_File_Save = wxNewId();
const long Courseplay_EditorFrame::idMenuQuit = wxNewId();
const long Courseplay_EditorFrame::idMenuAbout = wxNewId();
const long Courseplay_EditorFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(Courseplay_EditorFrame,wxFrame)
    //(*EventTable(Courseplay_EditorFrame)
    //*)
END_EVENT_TABLE()

Courseplay_EditorFrame::Courseplay_EditorFrame(wxWindow* parent,wxWindowID id)
{
    // Create images to use.
    wxPNGResource res;
    wxBitmap appIcon = res.GetBitmap(wxT("AppIcon"), 16, 16);

    //(*Initialize(Courseplay_EditorFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxBoxSizer* BoxSizer2;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, id, _("Courseplay Editor"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxFULL_REPAINT_ON_RESIZE, _T("id"));
    SetClientSize(wxSize(720,409));
    SetExtraStyle( GetExtraStyle() | wxFRAME_EX_METAL );
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(appIcon);
    	SetIcon(FrameIcon);
    }
    AuiManager1 = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
    Aui_Toolbar1 = new wxAuiToolBar(this, TLB_1, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
    Button1 = new wxButton(Aui_Toolbar1, ID_BUTTON1, _("Label"), wxPoint(35,17), wxSize(23,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Aui_Toolbar1->AddTool(ID_TLB1_BTN_NEW, _("Add"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, _("Add new waypoint"), _("Add new waypoint to the end of the route"), NULL);
    Aui_Toolbar1->AddControl(Button1, _("Item label"));
    Aui_Toolbar1->Realize();
    AuiManager1->AddPane(Aui_Toolbar1, wxAuiPaneInfo().Name(_T("TLB_1")).ToolbarPane().Caption(_("Pane caption")).CloseButton(false).Layer(10).Top().LeftDockable(false).RightDockable(false).Gripper());
    mainWindow = new wxScrolledWindow(this, ID_Main_Window, wxPoint(367,283), wxDefaultSize, wxSTATIC_BORDER|wxVSCROLL|wxHSCROLL|wxALWAYS_SHOW_SB|wxFULL_REPAINT_ON_RESIZE, _T("ID_Main_Window"));
    AuiManager1->AddPane(mainWindow, wxAuiPaneInfo().Name(_T("mainWindow")).CenterPane().Caption(_("Pane caption")));
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    courseList = new wxCheckListBox(Panel1, ID_COURSELIST, wxDefaultPosition, wxSize(200,107), 0, 0, wxSTATIC_BORDER|wxVSCROLL|wxALWAYS_SHOW_SB, wxDefaultValidator, _T("ID_COURSELIST"));
    courseList->Append(_("Course 1"));
    courseList->Append(_("Course 2"));
    courseList->Append(_("Course 3"));
    courseList->Append(_("Course 4"));
    courseList->Append(_("Course 5"));
    courseList->Append(_("Course 6"));
    courseList->Append(_("Course 7"));
    courseList->Append(_("Course 8"));
    courseList->Append(_("Course 9"));
    courseList->Append(_("Course 10"));
    BoxSizer1->Add(courseList, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    Button2 = new wxButton(Panel1, ID_BUTTON2, _("(Un)Select"), wxDefaultPosition, wxSize(62,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer2->Add(Button2, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(0,0,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button3 = new wxButton(Panel1, ID_BUTTON3, _("Up"), wxDefaultPosition, wxSize(23,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    BoxSizer2->Add(Button3, 0, wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 2);
    Button4 = new wxButton(Panel1, ID_BUTTON4, _("Dn"), wxDefaultPosition, wxSize(23,23), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    BoxSizer2->Add(Button4, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    Panel1->SetSizer(BoxSizer1);
    BoxSizer1->Fit(Panel1);
    BoxSizer1->SetSizeHints(Panel1);
    AuiManager1->AddPane(Panel1, wxAuiPaneInfo().Name(_T("PaneName")).DefaultPane().Caption(_("Course List")).CloseButton(false).Right().TopDockable(false).BottomDockable(false).Resizable(false));
    AuiManager1->Update();
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, ID_File_Load, _("&Load Route"), _("Load route from a savegame"), wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem4 = new wxMenuItem(Menu1, ID_File_Save, _("&Save Routes"), _("Save the loaded routes"), wxITEM_NORMAL);
    Menu1->Append(MenuItem4);
    MenuItem4->Enable(false);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("E&xit\tAlt-F4"), _("Close Courseplay Editor"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, wxST_SIZEGRIP|wxFULL_REPAINT_ON_RESIZE, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[3] = { -1, 150, 150 };
    int __wxStatusBarStyles_1[3] = { wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL };
    StatusBar1->SetFieldsCount(3,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(3,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    Center();

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&Courseplay_EditorFrame::OnClose);
    //*)
}

Courseplay_EditorFrame::~Courseplay_EditorFrame()
{
    //(*Destroy(Courseplay_EditorFrame)
    //*)
}

void Courseplay_EditorFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void Courseplay_EditorFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void Courseplay_EditorFrame::OnClose(wxCloseEvent& event)
{
    Destroy();
}
