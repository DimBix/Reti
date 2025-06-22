
//Client

var name= prompt("What's your name?");
while(name==""){
    name=prompt("You have to choose a name. \n What's your name?")
}

// Query DOM
var message = document.getElementById('message'),
   sender = document.getElementById('sender'),
   btn = document.getElementById('send'),
   output = document.getElementById('output'),
   feedback = document.getElementById('feedback');

sender.innerHTML=name;  
sender.value=name;

// Invio richiesta di connessione al server
var webSocket = io.connect();

// Listen for events
btn.addEventListener('click', function(){
   if (message.value!="" ){    
 	   webSocket.emit('messaggio', {
        message: message.value,
 	   sender: sender.value,
 	   });
 	   message.value = "";
   }
});

function handleInput() {
    if (message.value !== "") {
        webSocket.emit('typing', {
            sender: sender.value,
        });
        pauseInputListener(5000);
    }
}

message.addEventListener('input', handleInput);

function pauseInputListener(timeoutDuration) {
    message.removeEventListener('input', handleInput); // Remove the listener
    setTimeout(() => {
        message.addEventListener('input', handleInput); // Re-add the listener after the timeout
    }, timeoutDuration);
}


webSocket.on('typing', function(data){
   feedback.innerHTML = '';
   output.innerHTML += '<p><strong>' + data.sender + ': </strong>' + " is typing..." + '</p>';
});


webSocket.on('aggiornamento', function(data){
   feedback.innerHTML = '';
   output.innerHTML += '<p><strong>' + data.sender + ': </strong>' + data.message + '</p>';
});

