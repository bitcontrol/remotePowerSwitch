var mongoose = require('mongoose');

// Create schema for switch (written to by browsers, read by embedded computers)
var switchSchema = mongoose.Schema({
  devId: String, // A string offers more possibilities than a number
  date: Date,
  switch: String
});
// Compile schema into model
exports.switches = mongoose.model('switches', switchSchema);

// Create schema for status (written to by embedded computers, read by browsers)
var statusSchema = mongoose.Schema({
  devId: String, // A string offers more possibilities than a number
  date: Date,
  status: String
});
// Compile schema into model
exports.status = mongoose.model('status', statusSchema);