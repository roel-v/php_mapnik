<?php

namespace Mapnik;

/**
 * Represents a bounding rectangle around an area in a Cartesian plane, as
 * defined by its lower left (min) and upper right (max) corner points.
 * All values of an Envelope are returned as type double.
 */
class Envelope
{
    /**
     * Default constructor. Initialize an Envelope with all points set to 0.
     */
    function Envelope() {}
    /**
     * Initialize an Envelope with the minimum and maximum X and Y corner points
     * set to the passed in values.
     */
    function Envelope($minx, $miny, $maxx, $maxy) {}
    /**
     * Initialize an Envelope with the lower left coordinate set to the first
     * passed in argument, and the upper right coordinate to the second argument.
     */
    function Envelope(Coord2D $ll_coord, Coord2D, $ur_coord) {}
    /**
     * Returns the X component of the lower left point defining this envelope.
     */
	function getMinX() {}
    /**
     * Returns the Y component of the lower left point defining this envelope.
     */
	function getMinY() {}
    /**
     * Returns the X component of the upper right point defining this envelope.
     */
	function getMaxX() {}
    /**
     * Returns the Y component of the upper right point defining this envelope.
     */
	function getMaxY() {}
    /**
     * Returns the total width of the envelope.
     */
	function getWidth() {}
    /**
     * Returns the total height of the envelope.
     */
	function getHeight() {}
    /**
     * Sets a new width for the Envelope, by moving the left and right sides
     * towards or away from the center (depending on whether the Envelope is
     * being made wider or more narrow) by an equal amount.
     */
	function setWidth() {}
    /**
     * Sets a new height for the Envelope, by moving the top and bottom sides
     * towards or away from the center (depending on whether the Envelope is
     * being made taller or shorter) by an equal amount.
     */
	function setHeight() {}
    /**
     * Returns the center point of the Envelope as a Coord2D.
     */
	function getCenter() {}
    /**
     * Modifies the Envelope to include the point at the passed in coordinates.
     */
	function expandToInclude($x, $y) {}
    /**
     * Modifies the Envelope to include the point at the passed in coordinates.
     */
	function expandToInclude(Coord2D $coord) {}
    /**
     * Modifies the Envelope so that it includes the passed in Envelope.
     */
	function expandToInclude(Envelope $coord) {}
    /**
     * Returns true if the point at the passed in coordinates is within or on the border edges of the Envelope.
     */
	function contains($x, $y) {}
    /**
     * Returns true if the point at the passed in coordinates is within or on the border edges of the Envelope.
     */
	function contains(Coord2D $coord) {}
    /**
     * Returns true if the passed in Envelope is inside or on the border edges of the Envelope.
     */
	function contains(Envelope $envelope) {}
    /**
     * Returns true if the point at the passed in coordinates is within or on the border edges of the Envelope.
     */
	function intersects($x, $y) {}
    /**
     * Returns true if the point at the passed in coordinates is within or on the border edges of the Envelope.
     */
	function intersects(Coord2D $coord) {}
    /**
     * Returns true if the Envelope passed in has at least one of its corner inside or on the border edges of the Envelope.
     */
	function intersects(Envelope $envelope) {}
    /**
     * Returns an Envelope of the area that is common between the Envelope and
     * the passed in argument, or null if there is no overlapping area.
     * 
     * @returns object of class Envelope or null
     */
	function intersect(Envelope $envelope) {}
    /**
     * Moves the Envelope so that its center will be on the point at the passed in coordinate. Size will remain the same.
     */
	function reCenter($x, $y) {}
    /**
     * Set the minimum and maximum X and Y values of the corner points to the passed in values.
     */
	function init($minx, $miny, $maxx, $maxy) {}
}
