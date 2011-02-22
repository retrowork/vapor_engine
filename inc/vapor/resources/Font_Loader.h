/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#pragma once

#ifdef VAPOR_FONT_BITMAP

#include "Resources/ResourceLoader.h"	
#include "Resources/Font.h"
#include "Resources/BitmapFont.h"
#include "Resources/TTF.h"

namespace vapor {

//-----------------------------------//

/**
 * Loads a font description file format that can describe both TTF and
 * bitmap fonts. The format is very simple for now. This will be changed
 * later to be based on JSON.
 *
 * Example:
 *
 *		Calibri 12
 *		calibri-12.png
 *		calibri-12.dat
 *		16 16
 *
 * TODO:
 *
 *		"font": {
 *          "type": "texture"
 *			"name" : "Calibri",
 *			"size": 12,
 *			"glyphs": {
 *				"a": { "codepoint": 0x10, "uv": [[0, 0], [10, 20]] }
 *				"b": { "codepoint": 0x11, "uv": [[0, 0], [10, 20]] }
 *				"c": { "codepoint": 0x12, "uv": [[0, 0], [10, 20]] }
 *			}
 *		}   
 */

class RESOURCE_API Font_Loader : public ResourceLoader
{
	DECLARE_CLASS_()

public:

	Font_Loader();

	// Creates the resource with no data.
	RESOURCE_LOADER_PREPARE(BitmapFont)

	// Decode a font definition.
	virtual bool decode(const Stream& file, Resource* res);

	// Gets the name of this codec.
	GETTER(Name, const std::string, "FONTS")

	// Overrides this to return the right resource group.
	GETTER(ResourceGroup, ResourceGroup::Enum, ResourceGroup::Fonts)

protected:

	// Validates that the bitmap font format is okay.
	bool validateFont();

	// Parses the glyphs definition file.
	void parseGlyphs();

	BitmapFont* font;
	ImagePtr image;
	std::vector<Glyph> glyphs;

	std::vector<std::string> fontNameSizeInfo;
	std::vector<std::string> glyphSizeInfo;
	std::string imageFilename;
	std::string glyphsFilename;

	std::vector<std::string> lines;
	std::vector<byte> data;
};

//-----------------------------------//

} // end namespace

#endif