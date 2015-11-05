var fs = require("fs");
var http = require("http");
var path = require("path");
var url = require("url");

var httpMsgs = require("./httpMsgs");
var settings = require("./settings");

var baseDirectory = __dirname + "/../client";

var contentTypesByExtension = {
  ".css":  "text/css",
  ".html": "text/html",
  ".js":   "text/javascript",
  ".png":  "image/png"
};

http.createServer(function (req, res) { // Returns a new instance of http.Server
  // This function is automatically added to the 'request' event.
  console.log("Client connected.");
  console.log("Request method: " + req.method);

  // Could use req.url directly since it contains path as string, but it's
  // unsafer since it contains all characters as entered in the browser's
  // address line. url.parse() strips all characters that don't make up a
  // valid url from the end of the path.
  var reqUrlPath = url.parse(req.url).pathname;
  console.log("reqUrlPath: " + reqUrlPath);
  if (reqUrlPath === "/") {
    reqUrlPath += "index.html";
  }
  var fsPath = baseDirectory + reqUrlPath;
  console.log("fsPath: " + fsPath);

  switch (req.method) {
    case "GET":
      fs.stat(fsPath, function (err, stats) {
        if (!err) { // Kept separate from next line for differentiation of errors
          if (stats.isFile()) {
            var headerWritten = false;
            try {
              // Let the function decide what encoding is best (UTF8, binary, ...)
              var stream = fs.createReadStream(fsPath);
              stream.on("data", function (data) {
                // Many browsers work fine without having the 'Content-Type' set.
                // Better have it not set than set with a wrong value. Set it here
                // as an exercise.
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
              httpMsgs.send500(req, res, err);
            }
            finally {
              /*
              Don't do this here; could end msg before the 'end' callback has been
              fired above.
              */
              // res.end("The final end.");
              console.log("Client disconnected.");
            }
          }
          else {
            httpMsgs.send404(req, res);
            console.log("fs.stat(" + fsPath + ") returned fsStats.isFile()===false");
          }
        }
        else {
            httpMsgs.send404(req, res);
            console.log("fs.stat(" + fsPath + ") returned an error: " + err);
        }
      });
      break;
    default:
      httpMsgs.send405(req, res);
    break;
  }
}).listen(settings.webPort, function() {
  // This function is bound to the 'listening' event.
  // This event is emitted when the server has been bound after calling server.listen.
    console.log("Started listening at port " + settings.webPort);
});
