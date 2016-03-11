#ifndef IMAGE
#define IMAGE
//==============================================================================
///	
///	File: Image.hpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include <string>
#include "png.h"

//==============================================================================
/// Class
//==============================================================================

class Image {
    public:		
								Image			(void);	
								Image			(const Image &rhs);
        Image &					operator =		(const Image &rhs);	
        virtual					~Image			(void);
    	
	public:

		struct Pixel {
			Pixel(void) { r = g = b = a = 0; }
			unsigned char r,g,b,a;
		};
		
		/// Description
		/// \param param description
		/// \return description
		bool					load		(const std::string &s);

		/// Description
		/// \param param description
		/// \return description
		bool					save		(const std::string &s);

		/// Description
		/// \param param description
		/// \return description
		void					allocate	(int width, int height);
			
		/// Description
		/// \param param description
		/// \return description
		Pixel&					pixel   	(int x, int y) const;

		/// Description
		/// \param param description
		/// \return description
		Pixel&					pixel_clamped   (int x, int y) const;

		/// Description
		/// \param param description
		/// \return description
		Pixel&					pixel_wrapped   (int x, int y) const;

		/// Description
		/// \param param description
		/// \return description
		void					set_pixel	(int x, int y, Pixel &p);

		/// Description
		/// \param param description
		/// \return description
		int						width	    (void) const		{	return _data_width;	}

		/// Description
		/// \param param description
		/// \return description
		int						height  	(void) const		{	return _data_height;	}

	private:
		int				_data_width;
		int				_data_height;
		
		Pixel*			_data;
};

//==============================================================================
//==============================================================================

#endif
