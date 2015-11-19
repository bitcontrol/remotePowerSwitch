var mongoose = require('mongoose');

// Create schema for switch (written to by user)
var switchSchema = mongoose.Schema({
  date: Date,
  state: Boolean
});
// Compile schema into model
// Note: the name 'switch' can't be used since it is a keyword;
// thus the name 'switchOffOn' is being used instead
exports.switchOffOn = mongoose.model('switchOffOn', switchSchema);

// Create schema for status (written to by embedded computer)
var statusSchema = mongoose.Schema({
  date: Date,
  state: String
});
// Compile schema into model
exports.status = mongoose.model('status', switchSchema);