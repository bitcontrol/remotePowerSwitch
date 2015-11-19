// Create the database connection, handle its events
var db = require('./db');

// Create schemas and compile into models
var model = require('./model');

/**
 * @param function callback The function that is called to return the state of
 * the switch.
 * Assumed signature: function(err, res).
 */
function get(callback) {
  // TODO: Add implementation; 19-Nov-2015/ais
};

/**
 * @param value If the value is "on" (case insensitive), the heater will be
 * turned on. All other values switch the heater off.
 */
function set(value) {
  // TODO: Add implementation; 19-Nov-2015/ais
};
