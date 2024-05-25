#include "pch.h"
#include <wx/stackwalk.h>

// note: a bit of registration code is in dllApi.cpp to allow showing log console via lua

RTTR_REGISTRATION
{
     using namespace rttr;
// registration::class_<wxWindowList>("wxWindowList")
// .method("GetCount", &wxWindowList::GetCount)
// .method("IsEmpty", &wxWindowList::IsEmpty)
// .method("Item", &wxWindowList::Item)
// .method("Find", &wxWindowList::Find)
//  registerExtra<wxWindowList>();
// ;
//     // register all public data members and methods of wxWindowBase class
//     registration::class_<wxWindowBase>("wxWindowBase")
//         .method("GetId", &wxWindowBase::GetId)
//         .method("GetParent", &wxWindowBase::GetParent)
//         .method("GetGrandParent", &wxWindowBase::GetGrandParent)
//         .method("GetChildren", select_overload<const wxWindowList&() const>(&wxWindowBase::GetChildren))
//         .method("GetChildren", select_overload<wxWindowList&()>(&wxWindowBase::GetChildren))
//         .method("GetChildren", &wxWindowBase::GetChildren);
//  registerExtra<wxWindowBase>();

registration::class_<wxStackFrame>("wxStackFrame")
.method("GetAddress", &wxStackFrame::GetAddress)
.method("GetModule", &wxStackFrame::GetModule)
.method("GetLine", &wxStackFrame::GetLine)
.method("GetParamCount", &wxStackFrame::GetParamCount)
.method("GetParam", &wxStackFrame::GetParam)
.method("GetLevel", &wxStackFrame::GetLevel)
.method("GetFileName", &wxStackFrame::GetFileName)
.method("GetOffset", &wxStackFrame::GetOffset)
.method("HasSourceLocation", &wxStackFrame::HasSourceLocation);
	registerExtra<wxStackFrame>();

	registration::class_<wxStackWalker>("wxStackWalker")
		.method("Walk", &wxStackWalker::Walk);
	registerExtra<wxStackWalker>();
}