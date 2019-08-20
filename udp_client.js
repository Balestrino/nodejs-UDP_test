const udp = require('dgram')
const conf = require('./config/config')

//! creating a client socket
const client = udp.createSocket('udp4')

let sendCounter = 0;
let receiveCounter = 0;

//buffer msg
const data = Buffer.from('0')
//sending msg
setInterval(function() {
    client.send(data, conf.serverPort, conf.serverHost, error => {
        if (error) {
            console.log("error: ", error)
            client.close()
        } else {
            // console.log('Data sent on port ', conf.serverPort)
            sendCounter++;
        }
    })}
, 2);

//! creating a server socket
const server = udp.createSocket('udp4')
console.log("server: ", server)

// emits when any error occurs
server.on('error', (error) => {
    console.log("udp_server", "error", error)
    server.close()
})

//emits when socket is ready and listening for datagram msgs
server.on('listening', () => {
    const address = server.address()
    const port = conf.localPort
    const family = address.family
    const ipaddr = address.address

    console.log("udp_server", "info", 'Server is listening at port ' + port)
    console.log("udp_server", "info", 'Server ip :' + ipaddr)
    console.log("udp_server", "info", 'Server is IP4/IP6 : ' + family)
})

server.on('message', (msg, info) => {
    // console.log('Data received from server : ' + msg.toString())
    // console.log('Received %d bytes from %s:%d\n', msg.length, info.address, info.port)
    receiveCounter++;
})

server.bind(conf.localPort)

// CHECK TIMINGS
let myVar = setInterval(function(){ timer() }, 1000);

function timer() {
  let diff = sendCounter-receiveCounter;
  console.log("packets sent: ", sendCounter);
  console.log("packets received: ", receiveCounter);
  console.log("DIFF: ", diff)
}

function stopFunction() {
    clearInterval(myVar);
}

