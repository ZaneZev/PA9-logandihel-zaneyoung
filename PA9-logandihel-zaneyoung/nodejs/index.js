
//
// Server
// https://gist.github.com/branneman/0a77af5d10b93084e4f2
// https://nodejs.org/docs/latest-v7.x/api/net.html#net_class_net_socket
// https://nodejs.org/docs/latest-v7.x/api/net.html#net_event_connection

var net = require('net');
var server = new net.Server();
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
		else {
			socket.write("request_denied\u0000");
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