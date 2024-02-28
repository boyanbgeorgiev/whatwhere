document.addEventListener('DOMContentLoaded', function() {
    const messageInput = document.getElementById('message-input');
    const sendBtn = document.getElementById('send-btn');
    const messageContainer = document.getElementById('message-container');

    sendBtn.addEventListener('click', function() {
        const message = messageInput.value.trim();
        if (message !== '') {
            sendMessage(message);
            messageInput.value = ''; // Clear input field
        }
    });

    function sendMessage(message) {
        // Format the message with current timestamp
        const formattedMessage = `${getCurrentTime()} - ${message}`;

        // Append the message to the message container
        const messageElement = document.createElement('div');
        messageElement.textContent = formattedMessage;
        messageContainer.appendChild(messageElement);

        // Save the message to the text database file (you can replace this with your server-side code)
        saveMessageToFile(formattedMessage);
    }

    function getCurrentTime() {
        const now = new Date();
        const hours = now.getHours().toString().padStart(2, '0');
        const minutes = now.getMinutes().toString().padStart(2, '0');
        const seconds = now.getSeconds().toString().padStart(2, '0');
        return `${hours}:${minutes}:${seconds}`;
    }

    function saveMessageToFile(message) {
        // Here you would implement code to save the message to a text database file
        // This could involve sending an AJAX request to a server-side script that handles file writing
        // For example, in Node.js, you would use the 'fs' module to write to a file
        // For simplicity, we'll just log the message to the console
        console.log('Message saved:', message);
    }
});
