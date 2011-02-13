<?php

namespace Mapnik;

/**
 * Provides an interface to the Freetype font rendering library.
 */
class FreetypeEngine
{
	/**
	 * Registers a new font with the font engine. Pass in an absolute
	 * or relative (to the current working directory) path to a file
	 * in one of the formats Freetype supports (TrueType is the most
	 * common one, though).
	 */
	static function registerFont($font_path) { }
	/**
	 * Returns an array of all currently registered font face names.
	 */
	static function getFaceNames() { }
	/**
	 * Creates a font face by name. Pass in the name as it is returned
	 * by getFaceNames(); this is different from the file name, the
	 * face name is embedded in the font file.
	 */
	function createFace($face_name) { }
}
