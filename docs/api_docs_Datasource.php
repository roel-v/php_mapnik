<?php

namespace Mapnik;

/**
 * A simple class to represent a point in a Cartesian plane.
 */
class Datasource
{
    // parameters const& params() const
	function getParams() { }
    // virtual int type() const=0;
	function getType() { }
    // virtual featureset_ptr features(const query& q) const=0;
	function getFeatures(Query $q) { }
    // virtual featureset_ptr features_at_point(coord2d const& pt) const=0;
	function getFeaturesAtPoint(Coord2D $coord) { }
    // virtual Envelope<double> envelope() const=0;
	function getEnvelope() { }
    // virtual layer_descriptor get_descriptor() const=0;
	function getDescriptor() { }
}
