/**
 * This end point is written to by the embedded computers and read by the
 * browsers.
 */

// Create the database connection, handle its events
var db = require('./db');

// Create schemas and compile into models
var model = require('./model');

/**
 * @param String devId The device identifier of the Remote Power Switch.
 * @param function callback The function that is called to return the state of
 * the real switch and the outcome of the database transaction.
 * Assumed signature: function(err, res). The res parameter has one of the
 * values "off", "offline", "on".
 */
exports.get = function(devId, callback) {
  var query = {};
  query.devId = devId;
  model.status.find(query, function(err, docs) {
    if (!err) {
      if (docs.length > 0) { // Document(s) with this devId found?
        // Sort documents for date in descending order
        docs.sort(function(a,b){
          return b.date - a.date;
        });
        // Return latest doc (most recent db entry)
        var doc = {};
        doc.devId = docs[0].devId;
        doc.date = docs[0].date;
        doc.state = docs[0].state;
        callback(null, doc);
      }
      else { // No document with this devId found
        var doc = {};
        doc.error = "Unknown device identifier";
        callback(null, doc);
      }
    }
    else {
      callback(err, null);
    }
  });
};

/**
 * @param String devId The device identifier of the Remote Power Switch.
 * @param String value If the value is "on" (case insensitive), the Remote
 * Power Switch has the position 'on'. All other values indicate that the
 * switch is off.
 * @param function callback The function that is called to return the state of
 * the switch and the outcome of the database transaction.
 * Assumed signature: function(err, res). The res parameter has one of the
 * values "off" or "on".
 */
exports.set = function(devId, value, callback) {
  var query = {};
  query.devId = devId;
  model.status.find(query, function(err, docs) {
    if (!err) {
      if (docs.length > 0) { // Document(s) with this devId found?
        var doc = {};
        doc.devId = devId;
        doc.date = new Date();
        if (value === "on" || value === "On" || value === "oN" || value === "ON") {
          doc.state = "on";
        }
        else
        {
          doc.state = "off";
        }
        var status = new model.status(doc);
        status.save(function(err, status) {
          if (!err) {
            callback(null, doc);
          }
          else {
            callback(err, null);
          }
        });
      }
      else { // No document with this devId found
        var doc = {};
        doc.error = "Unknown device identifier";
        callback(null, doc);
      }
    }
    else {
      callback(err, null);
    }
  });
};