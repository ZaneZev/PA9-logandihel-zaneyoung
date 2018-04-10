// Constants
const port = 5000;

// Imports
const express = require("express");
const WebSocketServer = require("websocket").server;

// Mongo
//const MongoClient = require('mongodb').MongoClient;
//const MongoUrl = "mongodb://localhost:27017/";

// Express
const app = express();

const httpServer = app.listen(port, () => {
    console.log(`Listening on port ${port}`);
});

// Website
app.use(express.static(__dirname + '/html/'));

// WebSockets
const wsServer = new WebSocketServer({
    httpServer: httpServer
});

// all of our connections
/*
    [mac -> connection Object, ...]

*/
let connections = [];

wsServer.on('request', function(request) {
    console.log("got a request!");
    let connection = request.accept('test', request.origin);
    // ask for mac address
    connection.sendUTF(JSON.stringify({'command': 'address'}));

    connection.on('close', function() {
        for (let key in connections) {
            if (connections[key] === connection) {
                delete connections[key];
                console.log(`removed ${connection} from list of connections`);
                break;
            }
        }
    });

    connection.on('message', function(message) {
        if(message.type === 'utf8') {
            console.log(`Message Received: ${message.utf8Data}`);
        }
    });
});