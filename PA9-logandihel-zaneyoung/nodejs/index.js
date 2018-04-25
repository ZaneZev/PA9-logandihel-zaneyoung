
//
// Server
// https://gist.github.com/branneman/0a77af5d10b93084e4f2
// https://nodejs.org/docs/latest-v7.x/api/net.html#net_class_net_socket
// https://nodejs.org/docs/latest-v7.x/api/net.html#net_event_connection

var net = require('net');
var server = new net.Server();
var fs = require('fs');
const port = 3000;

var sockets = [];

server.on('connection', function(socket) {

	console.log('Socket is open!');
	socket.setEncoding('utf8');

	// events
	socket.on('data', function(data) {
		console.log('Received:', data);
		console.log(JSON.stringify(data));
		if (data == "connection_request") {
			sockets.push(socket);
			socket.write("request_granted\u0000");
		}
		else if (data == "bestscore_query") {
			var bestscore = 1000000;
			console.log("query besetscore");
			//vhttps://docs.nodejitsu.com/articles/file-system/how-to-read-files-in-nodejs/
			fs.readFile('./bestscore.txt', 'utf8', function (err,data) {
			  if (err) {
			    socket.write(bestscore+"\u0000");
			    console.log("query fail");
			    return;
			  }
			  bestscore = data;
			  console.log("query happy");
			  console.log(data);
			  socket.write(bestscore+"\u0000");
			});
		}
		else if (data.startsWith("newscore")) {
			socket.write("request_denied\u0000");
			var bestscore = 100000;
			var localscore = data.substr(7);
			console.log("localscore:"  + localscore);
			fs.readFile('./bestscore.txt', 'utf8', function (err,data) {
			  if (err) {
			    socket.write(bestscore+"\u0000");
			    console.log("query fail");
			    return;
			  }
			  bestscore = data;
			  console.log("read the file");
			  console.log(bestscore);

			  var bestever = "";
			  if (bestscore < localscore) {
			  		bestever = "" + bestscore;
			  }
			  else {
			  	bestever = "" + localscore;
			  }

			  if (bestscore < localscore) {
			  	fs.writeFile('./bestscore.txt', bestever, function (err,data) {
			  		if (err) {
			  			console.log("error in writing thing");
			  			return;
			  		}
			  		console.log("wooot");
			  	});
			  }

			});
		}
	});

	socket.on('close', function() {
		console.log('socket closed');
	});

	socket.on('error', function() {
		console.log('Socket error!');
	});
});

server.listen(port, function() {
	console.log('Server is listening on *:' + port);
});