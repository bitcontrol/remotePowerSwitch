var mongoose = require('mongoose');
var settings = require('./settings');

// Build the connection string
var dbURI = settings.dbConfig.server + '/' + settings.dbConfig.database;

// Create the database connection
var options = {
  // Keep socket alive when long intervals between requests
  // See here: http://mongoosejs.com/docs/connections.html
  keepAlive: 1
};
mongoose.connect(dbURI, options); // Returns the 'this' mongoose object

mongoose.connection.once('open', function () { // Event handler
  exports.conn = mongoose.connection;
});

// CONNECTION EVENTS
// When successfully connected
mongoose.connection.on('connected', function () { // Event handler
  console.log('Mongoose default connection to ' + dbURI + ' opened');
});

// If the connection throws an error
mongoose.connection.on('error',function (err) { // Event handler
  console.log('Mongoose default connection error: ' + err);
});

// When the connection is closed
mongoose.connection.on('disconnected', function () { // Event handler
  console.log('Mongoose default connection to ' + dbURI + ' closed');
});

// If the Node process ends, close the Mongoose connection
process.on('SIGINT', function() {
  mongoose.connection.close(function () {
    console.log('Mongoose default connection disconnected through app termination');
    process.exit(0);
  });
});