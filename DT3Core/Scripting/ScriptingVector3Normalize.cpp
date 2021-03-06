//==============================================================================
///	
///	File: ScriptingVector3Normalize.cpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3Core/Scripting/ScriptingVector3Normalize.hpp"
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

IMPLEMENT_FACTORY_CREATION_SCRIPT(ScriptingVector3Normalize,"VectorMath",NULL)
IMPLEMENT_PLUG_NODE(ScriptingVector3Normalize)

IMPLEMENT_PLUG_INFO_INDEX(_in)
IMPLEMENT_PLUG_INFO_INDEX(_length)
IMPLEMENT_PLUG_INFO_INDEX(_out)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ScriptingVector3Normalize)

	PLUG_INIT(_in,"In")
		.set_input(true)
		.affects(PLUG_INFO_INDEX(_out));
		
	PLUG_INIT(_length,"Length")
		.set_input(true)
		.affects(PLUG_INFO_INDEX(_out));

	PLUG_INIT(_out,"Out")
		.set_output(true);
        
END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ScriptingVector3Normalize::ScriptingVector3Normalize (void)
    :   _in				(PLUG_INFO_INDEX(_in), Vector3(0.0F,0.0F,0.0F)),
		_length			(PLUG_INFO_INDEX(_length), 1.0F),
		_out			(PLUG_INFO_INDEX(_out), Vector3(0.0F,0.0F,0.0F))
{  

}
		
ScriptingVector3Normalize::ScriptingVector3Normalize (const ScriptingVector3Normalize &rhs)
    :   ScriptingBase	(rhs),
		_in				(rhs._in),
		_length			(rhs._length),
		_out			(rhs._out)
{   

}

ScriptingVector3Normalize & ScriptingVector3Normalize::operator = (const ScriptingVector3Normalize &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ScriptingBase::operator = (rhs);

		_in = rhs._in;
		_length = rhs._length;
		_out = rhs._out;
	}
    return (*this);
}
			
ScriptingVector3Normalize::~ScriptingVector3Normalize (void)
{

}

//==============================================================================
//==============================================================================

void ScriptingVector3Normalize::initialize (void)
{
	ScriptingBase::initialize();
}

//==============================================================================
//==============================================================================

void ScriptingVector3Normalize::archive (const std::shared_ptr<Archive> &archive)
{
    ScriptingBase::archive(archive);

	archive->push_domain (class_id ());
	   
	*archive << ARCHIVE_PLUG(_in, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_length, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_out, DATA_PERSISTENT);
														     					
    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

DTboolean ScriptingVector3Normalize::compute (const PlugBase *plug)
{
	PROFILER(SCRIPTING);

    if (super_type::compute(plug))  return true;

	if (plug == &_out) {	
		if (_in->abs2() > 0.0F) {
			_out = _in->normalized() * _length;
		} else {
			_out = Vector3(0.0F,0.0F,0.0F);
		}
		_out.set_clean();
		return true;
	}
	
	return false;
}

//==============================================================================
//==============================================================================

} // DT3

