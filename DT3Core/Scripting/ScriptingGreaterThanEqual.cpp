//==============================================================================
///	
///	File: ScriptingGreaterThanEqual.cpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3Core/Scripting/ScriptingGreaterThanEqual.hpp"
#include "DT3Core/System/Factory.hpp"
#include "DT3Core/System/Profiler.hpp"
#include "DT3Core/Types/FileBuffer/ArchiveData.hpp"
#include "DT3Core/Types/FileBuffer/Archive.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_SCRIPT(ScriptingGreaterThanEqual,"Comparison",NULL)
IMPLEMENT_PLUG_NODE(ScriptingGreaterThanEqual)

IMPLEMENT_PLUG_INFO_INDEX(_in1)
IMPLEMENT_PLUG_INFO_INDEX(_in2)
IMPLEMENT_PLUG_INFO_INDEX(_out)
		
//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ScriptingGreaterThanEqual)

	PLUG_INIT(_in1,"In_1")
		.set_input(true)
		.affects(PLUG_INFO_INDEX(_out));
		
	PLUG_INIT(_in2,"In_2")
		.set_input(true)
		.affects(PLUG_INFO_INDEX(_out));

	PLUG_INIT(_out,"Out")
		.set_output(true);
        
END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ScriptingGreaterThanEqual::ScriptingGreaterThanEqual (void)
    :   _in1			(PLUG_INFO_INDEX(_in1), 0.0F),
		_in2			(PLUG_INFO_INDEX(_in2), 0.0F),
		_out			(PLUG_INFO_INDEX(_out), false)
{  

}
		
ScriptingGreaterThanEqual::ScriptingGreaterThanEqual (const ScriptingGreaterThanEqual &rhs)
    :   ScriptingBase	(rhs),
		_in1			(rhs._in1),
		_in2			(rhs._in2),
		_out			(rhs._out)
{   

}

ScriptingGreaterThanEqual & ScriptingGreaterThanEqual::operator = (const ScriptingGreaterThanEqual &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ScriptingBase::operator = (rhs);

		_in1 = rhs._in1;
		_in2 = rhs._in2;
		_out = rhs._out;
	}
    return (*this);
}
			
ScriptingGreaterThanEqual::~ScriptingGreaterThanEqual (void)
{

}

//==============================================================================
//==============================================================================

void ScriptingGreaterThanEqual::initialize (void)
{
	ScriptingBase::initialize();
}

//==============================================================================
//==============================================================================

void ScriptingGreaterThanEqual::archive (const std::shared_ptr<Archive> &archive)
{
    ScriptingBase::archive(archive);

	archive->push_domain (class_id ());
	   
	*archive << ARCHIVE_PLUG(_in1, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_in2, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_out, DATA_PERSISTENT);
														     					
    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

DTboolean ScriptingGreaterThanEqual::compute (const PlugBase *plug)
{
	PROFILER(SCRIPTING);

    if (super_type::compute(plug))  return true;

	if (plug == &_out) {
		_out = (_in1) >= (_in2);
		_out.set_clean();
		return true;
	}
	
	return false;
}

//==============================================================================
//==============================================================================

} // DT3

