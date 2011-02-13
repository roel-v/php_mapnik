<?php

namespace Mapnik;

/**
 * Simple class to represent an RGBA (red, green, blue, alpha)
 * value. All values are 8 bit, i.e. between 0 and 255.
 */
class Color
{
    /**
     * Returns the red component of the color.
     */
    function getRed() { }
    /**
     * Returns the green component of the color.
     */
	function getGreen() { }
    /**
     * Returns the blue component of the color.
     */
	function getBlue() { }
    /**
     * Returns the alpha component of the color.
     */
	function getAlpha() { }
    /**
     * Sets the red component of the color.
     */
	function setRed($red) { }
    /**
     * Sets the green component of the color.
     */
	function setGreen($green) { }
    /**
     * Sets the blue component of the color.
     */
	function setBlue($blue) { }
    /**
     * Sets the alpha component of the color.
     */
	function setAlpha($alpha) { }
    /**
     * Returns the color as a single 4-byte number, where each byte represents 
     * a component.
     */
	function rgba() { }
    /**
     * Returns a hex representation of the string in the form #0a0a0a.
     */
	function toHexString() { }
}
