/*
Lucas Zanella
*/

var CAMERA_HOST = '192.168.0.103',
	USERNAME = 'admin',
	PASSWORD = '19939495',
	PORT = 10080;


var http = require('http'),
	Cam = require('./lib/onvif').Cam;

new Cam({
	hostname: CAMERA_HOST,
	username: USERNAME,
	password: PASSWORD,
	port: PORT,
}, function(err) {
	if (err) {
		console.log('Connection Failed for ' + CAMERA_HOST + ' Port: ' + PORT + ' Username: ' + USERNAME + ' Password: ' + PASSWORD);
		return;
	}
	console.log('CONNECTED');
	
	this.absoluteMove({
		x: 1
		, y: 1
		, zoom: 1
	});
	
	this.getStreamUri({protocol:'RTSP'}, function(err, stream) {
		console.log(stream);
		//do something here?
		
	});
	
});

