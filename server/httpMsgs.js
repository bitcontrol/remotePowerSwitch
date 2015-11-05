var settings = require("./settings");

exports.send404 = function(req, resp) {
  resp.writeHead(404, "Resource not found", {"Content-Type": "text/html"});
  resp.write("<html><head><title>404</title></head><body>Error 404: Resource not found.</body></html>");
  console.log("Error 404 response sent.");
  resp.end();
};

exports.send405 = function(req, resp) {
  resp.writeHead(405, "Method not supported", {"Content-Type": "text/html"});
  resp.write("<html><head><title>405</title></head><body>Error 405: Method not supported.</body></html>");
  console.log("Error 405 response sent.");
  resp.end();
};

exports.send413 = function(req, resp) {
  resp.writeHead(413, "Requested entity too large", {"Content-Type": "text/html"});
  resp.write("<html><head><title>413</title></head><body>Error 413: Requested entity too large.</body></html>");
  console.log("Error 413 response sent.");
  resp.end();
};

exports.send500 = function(req, resp, err) {
  resp.writeHead(500, "Internal error", {"Content-Type": "text/html"});
  resp.write("<html><head><title>500</title></head><body>Error 500: Internal server error.</body></html>");
  console.log("Error 500 response sent.");
  resp.end();
};
