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
const long Courseplay_EditorFrame::TLB_1 = wxNewId();
const long Courseplay_EditorFrame::ID_Main_Window = wxNewId();
const long Courseplay_EditorFrame::ID_COURSELISTBOX = wxNewId();
const long Courseplay_EditorFrame::BTN_SELECTALLCOURSE = wxNewId();
const long Courseplay_EditorFrame::BTN_MOVECOURSEUP = wxNewId();
const long Courseplay_EditorFrame::BTN_MOVECOURSEDOWN = wxNewId();
const long Courseplay_EditorFrame::ID_STATICTEXT1 = wxNewId();
const long Courseplay_EditorFrame::TXT_COURSENAME = wxNewId();
const long Courseplay_EditorFrame::ID_PANEL1 = wxNewId();
const long Courseplay_EditorFrame::ID_STATICTEXT2 = wxNewId();
const long Courseplay_EditorFrame::ID_TEXTCTRL1 = wxNewId();
const long Courseplay_EditorFrame::ID_STATICTEXT3 = wxNewId();
const long Courseplay_EditorFrame::ID_TEXTCTRL2 = wxNewId();
const long Courseplay_EditorFrame::ID_STATICTEXT5 = wxNewId();
const long Courseplay_EditorFrame::ID_TEXTCTRL3 = wxNewId();
const long Courseplay_EditorFrame::ID_STATICTEXT4 = wxNewId();
const long Courseplay_EditorFrame::ID_TEXTCTRL4 = wxNewId();
const long Courseplay_EditorFrame::ID_CHECKBOX1 = wxNewId();
const long Courseplay_EditorFrame::ID_CHECKBOX2 = wxNewId();
const long Courseplay_EditorFrame::ID_CHECKBOX3 = wxNewId();
const long Courseplay_EditorFrame::ID_PANEL2 = wxNewId();
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

    // set default variables
    courseListSelectedAll   = false;
    courseListSelectedIndex = -1;

    // Create a input text validator
    wxArrayString validatorIncludeList;
    validatorIncludeList.Alloc(127-32);
    for (int i = 32; i < 127; i++)
    {
        validatorIncludeList.Add(wxString::Format(wxT("%c"), i));
    }
    wxTextValidator courseNameValidator(wxFILTER_INCLUDE_CHAR_LIST);
    courseNameValidator.SetIncludes(validatorIncludeList);
    courseNameValidator.SetBellOnError();

    //(*Initialize(Courseplay_EditorFrame)
    wxBoxSizer* BoxSizer4;
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxBoxSizer* BoxSizer2;
    wxMenu* Menu1;
    wxGridSizer* GridSizer1;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxFlexGridSizer* FlexGridSizer1;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("Courseplay Editor"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(1066,582));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(appIcon);
    	SetIcon(FrameIcon);
    }
    AuiManager1 = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
    Aui_Toolbar1 = new wxAuiToolBar(this, TLB_1, wxPoint(55,48), wxSize(236,24), wxAUI_TB_DEFAULT_STYLE);
    Aui_Toolbar1->AddTool(ID_TLB1_BTN_NEW, _("Add"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, _("Add new waypoint"), _("Add new waypoint to the end of the route"), NULL);
    Aui_Toolbar1->Realize();
    AuiManager1->AddPane(Aui_Toolbar1, wxAuiPaneInfo().Name(_T("TLB_1")).ToolbarPane().Caption(_("Pane caption")).CloseButton(false).Layer(10).Top().BestSize(wxSize(236,24)).Gripper());
    mainWindow = new wxScrolledWindow(this, ID_Main_Window, wxPoint(367,283), wxDefaultSize, wxSTATIC_BORDER|wxVSCROLL|wxHSCROLL|wxALWAYS_SHOW_SB|wxFULL_REPAINT_ON_RESIZE, _T("ID_Main_Window"));
    AuiManager1->AddPane(mainWindow, wxAuiPaneInfo().Name(_T("mainWindow")).CenterPane().Caption(_("Pane caption")));
    panelCourseList = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER, _T("ID_PANEL1"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    courseList = new wxCheckListBox(panelCourseList, ID_COURSELISTBOX, wxDefaultPosition, wxSize(200,124), 0, 0, wxVSCROLL|wxALWAYS_SHOW_SB, wxDefaultValidator, _T("ID_COURSELISTBOX"));
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
    BoxSizer1->Add(courseList, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    selectAllCourse = new wxButton(panelCourseList, BTN_SELECTALLCOURSE, _("(Un)Select All"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("BTN_SELECTALLCOURSE"));
    BoxSizer2->Add(selectAllCourse, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(15,20,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    moveCourseUp = new wxButton(panelCourseList, BTN_MOVECOURSEUP, _("Up"), wxDefaultPosition, wxSize(23,23), 0, wxDefaultValidator, _T("BTN_MOVECOURSEUP"));
    moveCourseUp->Disable();
    BoxSizer2->Add(moveCourseUp, 0, wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 2);
    moveCourseDown = new wxButton(panelCourseList, BTN_MOVECOURSEDOWN, _("Dn"), wxDefaultPosition, wxSize(23,23), 0, wxDefaultValidator, _T("BTN_MOVECOURSEDOWN"));
    moveCourseDown->Disable();
    BoxSizer2->Add(moveCourseDown, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    StaticText1 = new wxStaticText(panelCourseList, ID_STATICTEXT1, _("Course Name:"), wxDefaultPosition, wxSize(69,16), 0, _T("ID_STATICTEXT1"));
    BoxSizer3->Add(StaticText1, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    courseName = new wxTextCtrl(panelCourseList, TXT_COURSENAME, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, courseNameValidator, _T("TXT_COURSENAME"));
    courseName->SetMaxLength(20);
    courseName->Disable();
    BoxSizer3->Add(courseName, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer3, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    panelCourseList->SetSizer(BoxSizer1);
    BoxSizer1->Fit(panelCourseList);
    BoxSizer1->SetSizeHints(panelCourseList);
    AuiManager1->AddPane(panelCourseList, wxAuiPaneInfo().Name(_T("PaneName")).DefaultPane().Caption(_("Course List")).CloseButton(false).Right().Resizable(false));
    panelWpProp = new wxPanel(this, ID_PANEL2, wxPoint(952,334), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    BoxSizer4 = new wxBoxSizer(wxVERTICAL);
    FlexGridSizer1 = new wxFlexGridSizer(4, 2, 0, 0);
    FlexGridSizer1->AddGrowableCol(1);
    StaticText2 = new wxStaticText(panelWpProp, ID_STATICTEXT2, _("Pos X"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer1->Add(StaticText2, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wpPropPosX = new wxTextCtrl(panelWpProp, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(150,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    wpPropPosX->Disable();
    FlexGridSizer1->Add(wpPropPosX, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(panelWpProp, ID_STATICTEXT3, _("Pos Y"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    FlexGridSizer1->Add(StaticText3, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wpPropPosY = new wxTextCtrl(panelWpProp, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(150,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    wpPropPosY->Disable();
    FlexGridSizer1->Add(wpPropPosY, 0, wxTOP|wxBOTTOM|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 2);
    StaticText5 = new wxStaticText(panelWpProp, ID_STATICTEXT5, _("Angle"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    FlexGridSizer1->Add(StaticText5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wpPropAngle = new wxTextCtrl(panelWpProp, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxSize(150,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    wpPropAngle->Disable();
    FlexGridSizer1->Add(wpPropAngle, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(panelWpProp, ID_STATICTEXT4, _("Speed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    FlexGridSizer1->Add(StaticText4, 0, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wpPropSpeed = new wxTextCtrl(panelWpProp, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxSize(150,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    wpPropSpeed->Disable();
    FlexGridSizer1->Add(wpPropSpeed, 0, wxTOP|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 2);
    BoxSizer4->Add(FlexGridSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1 = new wxGridSizer(0, 2, 0, 0);
    wpPropReverse = new wxCheckBox(panelWpProp, ID_CHECKBOX1, _("Reverse"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    wpPropReverse->SetValue(false);
    GridSizer1->Add(wpPropReverse, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    wpPropWaitPoint = new wxCheckBox(panelWpProp, ID_CHECKBOX2, _("Waiting Point"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    wpPropWaitPoint->SetValue(false);
    GridSizer1->Add(wpPropWaitPoint, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    wpPropCrossing = new wxCheckBox(panelWpProp, ID_CHECKBOX3, _("Crossing"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    wpPropCrossing->SetValue(false);
    GridSizer1->Add(wpPropCrossing, 1, wxTOP|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(GridSizer1, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    panelWpProp->SetSizer(BoxSizer4);
    BoxSizer4->Fit(panelWpProp);
    BoxSizer4->SetSizeHints(panelWpProp);
    AuiManager1->AddPane(panelWpProp, wxAuiPaneInfo().Name(_T("wpProperty")).DefaultPane().Caption(_("Waypoint Info & Property")).CloseButton(false).Right().Resizable(false));
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

    Connect(ID_COURSELISTBOX,wxEVT_COMMAND_CHECKLISTBOX_TOGGLED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnCourseListToggled);
    Connect(ID_COURSELISTBOX,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnCourseListSelect);
    Connect(BTN_SELECTALLCOURSE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnSelectAllCourseClick);
    Connect(BTN_MOVECOURSEUP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnMoveCourseUpClick);
    Connect(BTN_MOVECOURSEDOWN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnMoveCourseDownClick);
    Connect(TXT_COURSENAME,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&Courseplay_EditorFrame::OnCourseNameEnter);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnWpPropReverseClick);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnWpPropWaitPointClick);
    Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnWpPropCrossingClick);
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

void Courseplay_EditorFrame::OnCourseListToggled(wxCommandEvent& event)
{
    courseListSelectedAll = true;

    for (int i = 0; i < (int)courseList->GetCount(); i++)
    {
        if (!courseList->IsChecked(i))
        {
            courseListSelectedAll = false;
            break;
        }
    }

    // TODO: Update drawArea to show or hide the route.
}

void Courseplay_EditorFrame::OnCourseListSelect(wxCommandEvent& event)
{
    courseListSelectedIndex = event.GetInt();

    moveCourseUp->Enable(courseListSelectedIndex != 0);
    moveCourseDown->Enable(courseListSelectedIndex < (int)courseList->GetCount() - 1);

    courseName->SetValue(courseList->GetString(courseListSelectedIndex));

    if (!courseName->IsEnabled())
        courseName->Enable();
    courseName->SetFocus();
    courseName->SetInsertionPointEnd();

}

void Courseplay_EditorFrame::OnSelectAllCourseClick(wxCommandEvent& event)
{
    for (int i = 0; i < (int)courseList->GetCount(); i++)
    {
        if (!courseListSelectedAll)
            courseList->Check(i, true);
        else
            courseList->Check(i, false);
    }

    courseListSelectedAll = (!courseListSelectedAll);
    //SetStatusText(wxString::Format(wxT("Index: %d"), (int)courseListSelectedAll),1);

    // TODO: Update drawArea to show or hide routes
}

void Courseplay_EditorFrame::OnCourseNameEnter(wxCommandEvent& event)
{
    courseList->SetString(courseListSelectedIndex, courseName->GetValue());
    courseName->SetValue(wxT(""));
    courseName->Enable(false);
    courseList->Deselect(courseListSelectedIndex);
    courseListSelectedIndex = -1;

    moveCourseUp->Enable(false);
    moveCourseDown->Enable(false);
}

void Courseplay_EditorFrame::OnMoveCourseUpClick(wxCommandEvent& event)
{
    int oldpos = courseListSelectedIndex; // need this for the list to update.

    CheckListItem item;
    item.text = courseList->GetString(courseListSelectedIndex);
    item.isChecked = courseList->IsChecked(courseListSelectedIndex);

    courseList->Delete(courseListSelectedIndex);

    courseListSelectedIndex--;

    courseList->Insert(item.text, courseListSelectedIndex);

    courseList->Check(courseListSelectedIndex, item.isChecked);
    courseList->SetSelection(courseListSelectedIndex);

    // TODO: Move the course up in the course list (The real course list).

    moveCourseUp->Enable(courseListSelectedIndex != 0);
    moveCourseDown->Enable(courseListSelectedIndex < (int)courseList->GetCount() - 1);
}

void Courseplay_EditorFrame::OnMoveCourseDownClick(wxCommandEvent& event)
{
    int oldpos = courseListSelectedIndex; // need this for the list to update.

    CheckListItem item;
    item.text = courseList->GetString(courseListSelectedIndex);
    item.isChecked = courseList->IsChecked(courseListSelectedIndex);

    courseList->Delete(courseListSelectedIndex);

    courseListSelectedIndex++;

    if (courseListSelectedIndex == (int)courseList->GetCount())
        courseList->Append(item.text);
    else
        courseList->Insert(item.text, courseListSelectedIndex);

    courseList->Check(courseListSelectedIndex, item.isChecked);
    courseList->SetSelection(courseListSelectedIndex);

    // TODO: Move the course down in the course list (The real course list).

    moveCourseUp->Enable(courseListSelectedIndex != 0);
    moveCourseDown->Enable(courseListSelectedIndex < (int)courseList->GetCount() - 1);
 }

void Courseplay_EditorFrame::OnWpPropReverseClick(wxCommandEvent& event)
{
}

void Courseplay_EditorFrame::OnWpPropWaitPointClick(wxCommandEvent& event)
{
}

void Courseplay_EditorFrame::OnWpPropCrossingClick(wxCommandEvent& event)
{
    //wxTextValidator(wxFILTER_ALPHANUMERIC | wxFILTER_INCLUDE_LIST)::SetIncludes(wxArrayString {wxT(" ")}))
}
