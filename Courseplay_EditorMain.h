/***************************************************************
 * Name:      Courseplay_EditorMain.h
 * Purpose:   Defines Application Frame
 * Author:    Claus G. Pedersen aka Satis (satissis@gmail.com)
 * Created:   2013-06-08
 * Copyright: Claus G. Pedersen aka Satis (https://github.com/Satissis/CourseplayEditor)
 * License:
 **************************************************************/

#ifndef COURSEPLAY_EDITORMAIN_H
#define COURSEPLAY_EDITORMAIN_H

//(*Headers(Courseplay_EditorFrame)
#include <wx/scrolwin.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/checklst.h>
#include <wx/aui/aui.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

struct CheckListItem
{
    wxString text;
    bool isChecked;
};

class Courseplay_EditorFrame: public wxFrame
{
    public:

        Courseplay_EditorFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~Courseplay_EditorFrame();

    private:
        bool courseListSelectedAll;
        int  courseListSelectedIndex;

    private:

        //(*Handlers(Courseplay_EditorFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnCourseListToggled(wxCommandEvent& event);
        void OnCourseListSelect(wxCommandEvent& event);
        void OnSelectAllCourseClick(wxCommandEvent& event);
        void OnCourseNameEnter(wxCommandEvent& event);
        void OnMoveCourseUpClick(wxCommandEvent& event);
        void OnMoveCourseDownClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(Courseplay_EditorFrame)
        static const long ID_TLB1_BTN_NEW;
        static const long TLB_1;
        static const long ID_Main_Window;
        static const long ID_COURSELISTBOX;
        static const long BTN_SELECTALLCOURSE;
        static const long BTN_MOVECOURSEUP;
        static const long BTN_MOVECOURSEDOWN;
        static const long ID_STATICTEXT1;
        static const long TXT_COURSENAME;
        static const long ID_PANEL1;
        static const long ID_File_Load;
        static const long ID_File_Save;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(Courseplay_EditorFrame)
        wxAuiManager* AuiManager1;
        wxCheckListBox* courseList;
        wxButton* moveCourseDown;
        wxButton* moveCourseUp;
        wxAuiToolBar* Aui_Toolbar1;
        wxMenuItem* MenuItem4;
        wxTextCtrl* courseName;
        wxButton* selectAllCourse;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxScrolledWindow* mainWindow;
        wxMenuItem* MenuItem3;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // COURSEPLAY_EDITORMAIN_H
