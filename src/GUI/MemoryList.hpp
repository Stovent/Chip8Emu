#ifndef MEMORYLIST_HPP
#define MEMORYLIST_HPP

#include <wx/listctrl.h>

class MemoryList : public wxListCtrl
{
    const uint8_t* memory;

public:
    MemoryList(wxWindow* parent, const uint8_t* mem);

    virtual wxString OnGetItemText(long item, long column) const;
};

#endif // MEMORYLIST_HPP
