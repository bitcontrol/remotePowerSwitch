var fs = require("fs");
var http = require("http");
var path = require("path");
var url = require("url");

var httpMsgs = require("./httpMsgs");
var settings = require("./settings");
var status = require("./status");
var switches = require("./switches");

var baseDirectory = __dirname + "/../client";

var contentTypesByExtension = {
  ".css":  "text/css",
  ".html": "text/html",
  ".js":   "text/javascript",
  ".png":  "image/png"
};

http.createServer(function (req, res) { // Returns a new instance of http.Server
  // This function is automatically added to the 'request' event.
  console.log('Client connected.');
  console.log('Request method: ' + req.method);

  // Could use req.url directly since it contains path as string, but it's
  // unsafer since it contains all characters as entered in the browser's
  // address line. url.parse() strips all characters that don't make up a
  // valid url from the end of the path.
  var reqUrlPath = url.parse(req.url).pathname;
  console.log('reqUrlPath: ' + reqUrlPath);
  if (reqUrlPath === '/') {
    reqUrlPath += 'index.html';
  }
  var fsPath = baseDirectory + reqUrlPath;
  console.log('fsPath: ' + fsPath);

  fs.stat(fsPath, function (err, stats) {
    if (!err) {
      if (stats.isFile()) { // Serve static pages like index.html?
        switch (req.method) {
          case "GET":
            var headerWritten = false;
            try {
              // Let the function decide what encoding is best (UTF8, binary, ...)
              var stream = fs.createReadStream(fsPath);
              stream.on("data", function (data) {
                // Many browsers work fine without having the 'Content-Type' set.
                // Better have it not set than set with a wrong value.
                if (!headerWritten) {
                  var header = {};
                  var contentType = contentTypesByExtension[path.extname(reqUrlPath)];
                  if (contentType) {
                    header["Content-Type"] = contentType;
                  }
                  res.writeHead(200, header);
                  headerWritten = true;
                }
                res.write(data);
              });
              stream.on("end", function() {
                res.end();
                console.log("Ok 200 response sent."); // The happy end
              })
              stream.on("error", function (err) {
                console.log(err);
                httpMsgs.send404(req, res);
              });
            }
            catch (err) {
              console.log(err);
              httpMsgs.send500(req, res);
            }
          break;
          default:
            httpMsgs.send405(req, res); // Method not supported
          break;
        }
      }
      else {
          httpMsgs.send404(req, res);
          console.log("fs.stat(" + fsPath + ") returned an error: " + err);
      }
    }
    else { // It's not a file; serve REST query
      var urlTokens = reqUrlPath.split("/"); // urlTokens[0] is ""
      switch (urlTokens[1]) { // Contains end point
        // End point 'status'
        case "status":
          if (urlTokens.length === 3) {
            if (req.method === "GET") {
              // urlTokens[2] is the device identifier
              status.get(urlTokens[2], function(err, sta) {
                if (!err) {
                  res.writeHead(200, "Request succeeded",
                                {"Content-Type": "application/json"});
                  res.write(JSON.stringify(sta));
                  res.end();
                  console.log("Ok 200 response sent."); // The happy end
                }
                else {
                  console.log(err);
                  httpMsgs.send500(req, res);
                }
              });
            }
            else {
              httpMsgs.send405(req, res); // Method not supported
              console.log(req.method + " " + urlTokens[0] + "/" + urlTokens[1]
                          + ": method not supported");
            }
          }
          else if (urlTokens.length === 4) {
            if (req.method === "POST") {
              // urlTokens[2] is the device identifier, urlTokens[3] is the
              // device state (on, off)
              status.set(urlTokens[2], urlTokens[3], function(err, sta) {
                if (!err) {
                  res.writeHead(200, "Request succeeded",
                                {"Content-Type": "application/json"});
                  res.write(JSON.stringify(sta));
                  res.end();
                  console.log("Ok 200 response sent."); // The happy end
                }
                else {
                  console.log(err);
                  httpMsgs.send500(req, res);
                }
              });
            }
            else {
              httpMsgs.send405(req, res); // Method not supported
              console.log(req.method + " " + urlTokens[0] + "/" + urlTokens[1]
                          + ": method not supported");
            }
          }
          else {
            httpMsgs.send404(req, res);
            console.log(fsPath + ": REST resource not found");
          };
        break;
        // End point 'switches'
        case "switches":
          if (urlTokens.length === 3) {
            if (req.method === "GET") {
              // urlTokens[2] is the device identifier
              switches.get(urlTokens[2], function(err, sta) {
                if (!err) {
                  res.writeHead(200, "Request succeeded",
                                {"Content-Type": "application/json"});
                  res.write(JSON.stringify(sta));
                  res.end();
                  console.log("Ok 200 response sent."); // The happy end
                }
                else {
                  console.log(err);
                  httpMsgs.send500(req, res);
                }
              });
            }
            else {
              httpMsgs.send405(req, res); // Method not supported
              console.log(req.method + " " + urlTokens[0] + "/" + urlTokens[1]
                          + ": method not supported");
            }
          }
          else if (urlTokens.length === 4) {
            if (req.method === "POST") {
              // urlTokens[2] is the device identifier, urlTokens[3] is the
              // device state (on, off)
              switches.set(urlTokens[2], urlTokens[3], function(err, sta) {
                if (!err) {
                  res.writeHead(200, "Request succeeded",
                                {"Content-Type": "application/json"});
                  res.write(JSON.stringify(sta));
                  res.end();
                  console.log("Ok 200 response sent."); // The happy end
                }
                else {
                  console.log(err);
                  httpMsgs.send500(req, res);
                }
              });
            }
            else {
              httpMsgs.send405(req, res); // Method not supported
              console.log(req.method + " " + urlTokens[0] + "/" + urlTokens[1]
                          + ": method not supported");
            }
          }
          else {
            httpMsgs.send404(req, res);
            console.log(fsPath + ": REST resource not found");
          };
        break;
        default: // Unknown end point
          httpMsgs.send404(req, res);
          console.log(fsPath + ": unknown end point");
        break;
      }
    }
  });
}).listen(settings.webPort, function() {
  // This function is bound to the 'listening' event.
  // This event is emitted when the server has been bound after calling server.listen.
    console.log("Started listening at port " + settings.webPort);
});