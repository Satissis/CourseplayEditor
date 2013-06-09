#ifndef __wx_PNG_Resource__
#define __wx_PNG_Resource__

#include <wx/wx.h>

class wxPNGResource
{
public:
	wxImage		GetImage(const wxString& t_name, int width = 0, int height = 0);
	wxImage		GetImage(const wxString& t_name, wxPoint size);
	wxBitmap	GetBitmap(const wxString& t_name, int width = 0, int height = 0);
	wxBitmap	GetBitmap(const wxString& t_name, wxPoint size);

protected:
	bool		LoadDataFromResource(char*& t_data, DWORD& t_dataSize, const wxString& t_name);
	wxImage	GetImageMemory(const char* t_data, const DWORD t_size);

private:

};

#endif
