<?php

namespace Mapnik;

/**
 * Represents a spatial query. mapnik::query has several facilities to pass
 * informatino to various types of data sources.
 * For more information on the scale_denominator used, see https://trac.mapnik.org/wiki/ScaleAndPpi .
 */
class Query
{
    // explicit query(const Envelope<double>& bbox, double resolution, double scale_denominator)
    // explicit query(const Envelope<double>& bbox, double resolution)
    /**
     * Constructs a query within the passed in bounding box and resolution.
     */
    function Query(Envelope $bbox, double resolution) { }
    /**
     * Constructs a query within the passed in bounding box, resolution and scale_denominator.
     */
    function Query(Envelope $bbox, double resolution, double scale_denominator) { }
    /**
     * Returns the resolution of the query as a doube.
     */
    function getResolution() { }
    /**
     * Returns the resolution of the query as a doube.
     */
    function getScaleDenominator() { }
    // const Envelope<double>& get_bbox() const
    /**
     * Returns the bounding box of this query.
     */
    function getBoundingBox() { }
    // void add_property_name(const std::string& name)
    /**
     * 
     */
    function addPropertyName($name) { }
    // const std::set<std::string>& property_names() const
    /**
     * Returns all property names of this query as an array.
     */
    function getPropertyNames() { }
}
