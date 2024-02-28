function sendMessage() {
    var message = document.getElementById("user-input").value;
    if (message.trim() !== "") {
        var chatBox = document.getElementById("chat-box");
        var newMessage = document.createElement("div");
        newMessage.textContent = message;
        chatBox.appendChild(newMessage);
        saveMessage(message); // Call function to save message
        document.getElementById("user-input").value = ""; // Clear input field
        chatBox.scrollTop = chatBox.scrollHeight; // Scroll to bottom
    }
}

function saveMessage(message) {
    // Send message to server to save in the text database
    fetch('/save-message', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ message: message }),
    })
    .then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        return response.json();
    })
    .then(data => {
        console.log('Message saved:', data);
    })
    .catch(error => {
        console.error('There was a problem saving the message:', error);
    });
}
