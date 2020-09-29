#include "MemoryList.hpp"
#include "../utils.hpp"
#include "../Chip8/Chip8.hpp"

MemoryList::MemoryList(wxWindow* parent, const uint8_t* mem) : wxListCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_VIRTUAL | wxLC_HRULES | wxLC_VRULES)
{
    memory = mem;

    wxListItem addrCol;
    addrCol.SetId(0);
    addrCol.SetText("Address");
    addrCol.SetWidth(60);
    InsertColumn(0, addrCol);

    wxListItem valueCol;
    valueCol.SetId(1);
    valueCol.SetText("Value");
    valueCol.SetWidth(75);
    InsertColumn(1, valueCol);

    SetItemCount(CHIP8_MEMORY_SIZE);
}

wxString MemoryList::OnGetItemText(long item, long column) const
{
    if(column == 0)
        return toHex(item);
    else
        return "(0x" + toHex(memory[item]) + ") " + std::to_string(memory[item]);
}
