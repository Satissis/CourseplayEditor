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
#include <wx/menu.h>
#include <wx/aui/aui.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

class Courseplay_EditorFrame: public wxFrame
{
    public:

        Courseplay_EditorFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~Courseplay_EditorFrame();

    private:

        //(*Handlers(Courseplay_EditorFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        //*)

        //(*Identifiers(Courseplay_EditorFrame)
        static const long ID_TLB1_BTN_NEW;
        static const long TLB_1;
        static const long ID_Main_Window;
        static const long ID_File_Load;
        static const long ID_File_Save;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(Courseplay_EditorFrame)
        wxAuiManager* AuiManager1;
        wxAuiToolBar* Aui_Toolbar1;
        wxMenuItem* MenuItem4;
        wxScrolledWindow* mainWindow;
        wxMenuItem* MenuItem3;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // COURSEPLAY_EDITORMAIN_H
