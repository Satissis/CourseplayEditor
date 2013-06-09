#include <wx/mstream.h>

#include "wxPNGResource.h"

wxImage wxPNGResource::GetImage(const wxString& t_name, int width, int height)
{
	wxImage	r_imagePtr;

	char*	a_data		= 0;
	DWORD	a_dataSize	= 0;

	if(LoadDataFromResource(a_data, a_dataSize, t_name))
	{
		r_imagePtr = GetImageMemory(a_data, a_dataSize);

		// only scale if width and height is set and if the resource image is not the same size!
		if (width != 0 && height != 0 && (r_imagePtr.GetWidth() != width || r_imagePtr.GetHeight() != height))
			r_imagePtr = r_imagePtr.Scale(width, height);
	}

	return r_imagePtr;
}

wxImage wxPNGResource::GetImage(const wxString& t_name, wxPoint size)
{
	return GetImage(t_name, size.x, size.y);
}

wxBitmap wxPNGResource::GetBitmap(const wxString& t_name, int width, int height)
{
	return wxBitmap(GetImage(t_name, width, height));
}

wxBitmap wxPNGResource::GetBitmap(const wxString& t_name, wxPoint size)
{
	return GetBitmap(t_name, size.x, size.y);
}

bool wxPNGResource::LoadDataFromResource(char*& t_data, DWORD& t_dataSize, const wxString& t_name)
{
	bool	r_result	= false;
	HGLOBAL	a_resHandle	= 0;
	HRSRC	a_resource;

	a_resource = FindResource(0, t_name.wchar_str(), RT_RCDATA);

	if(0 != a_resource)
	{
		a_resHandle = LoadResource(NULL, a_resource);
		if (0 != a_resHandle)
		{
			t_data = (char*)LockResource(a_resHandle);
			t_dataSize = SizeofResource(NULL, a_resource);
			r_result = true;
		}
	}

	return r_result;
}

wxImage wxPNGResource::GetImageMemory(const char* t_data, const DWORD t_size)
{
	wxMemoryInputStream a_is(t_data, t_size);
	return wxImage(a_is, wxBITMAP_TYPE_PNG, -1);
}
