/**
 * This end point is written to by the browsers and read by the embedded
 * computers.
 */

// Create the database connection, handle its events
var db = require('./db');

// Create schemas and compile into models
var model = require('./model');

/**
 * @param function callback The function that is called to return the state of
 * the switch and the outcome of the database transaction.
 * Assumed signature: function(err, res). The res parameter is an object with
 * the attributes 'devId', 'date' and 'state'. In case no document with this
 * device identifier was found, the res object contains the only attribute
 * 'error'.
 */
function get(devId, callback) {
  var query = {};
  query.devId = devId;
  model.switches.find(query, function(err, docs) {
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
        doc.switch = docs[0].switch;
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
exports.get = get; // This function is used inside and outside this module

/**
 * This function updates the database collection 'switches', if the requested
 * new state of the switch is different from the current state. If this isn't
 * the case, this function doesn't update the database, but returns the
 * document that reflects the current state.
 * @param String devId The device identifier of the Remote Power Switch.
 * @param String value If the value is "on" (case insensitive), the Remote
 * Power Switch will be turned on. All other values turn the switch off.
 * @param function callback The function that is called to return the state of
 * the switch and the outcome of the database transaction.
 * Assumed signature: function(err, res). The res parameter is an object with
 * the attributes 'devId', 'date' and 'state'. In case no document with this
 * device identifier was found, the res object contains the only attribute
 * 'error'.
 */
exports.set = function(devId, value, callback) {
  var doc = {};
  doc.devId = devId;
  doc.date = new Date();
  if (value === "on" || value === "On" || value === "oN" || value === "ON") {
    doc.switch = "on";
  }
  else
  {
    doc.switch = "off";
  }
  // If the current state is equal to the new state, don't store the
  // request in the database.
  get(devId, function(err, res) { // Retrieve the latest state
    if (!err) {
      if (res.error === undefined) { // Document found?
        if (doc.switch !== res.switch) { // New state != old state?
          // Save new state in the database
          var switchOnOff = new model.switches(doc); // 'switch' is a keyword
          switchOnOff.save(function(err, switchOnOff) {
            if (!err) {
              callback(null, doc);
            }
            else {
              callback(err, null);
            }
          });
        } // New state == old state; return old state document
        else {
          callback(null, res);
        }
      }
      else { // No document with this devId found
        callback(null, res);
      }
    }
    else { // Database error
      callback(err, null);
    }
  });
};