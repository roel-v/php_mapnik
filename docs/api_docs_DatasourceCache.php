<?php

namespace Mapnik;

/**
 * Abstract class with a number of static members to set up and query
 * the data I/O plugins.
 */
class DatasourceCache
{
    /**
     * Searches the given directory for all files ending in '.plugin',
     * and tries to load those as data sources.
     */
    function registerDatasources($path) {}
    /**
     * Returns an array of all plugin names that were found by previous
     * calls to getPluginNames(). The name is only the first part of the
     * filename, e.g. for shapefile.input it's 'shapefile'.
     */
    function getPluginNames() {}
    /**
     * Instantiates a data source by name. The name is the base of the filename
     * (e.g. for shapefile.input it's 'shapefile') and is the name as returned
     * by getPluginNames().
     * @return DataSource
     */
    function createDatasource(Parameters $parameters) {}
}
