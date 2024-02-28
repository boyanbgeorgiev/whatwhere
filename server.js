const express = require('express');
const bodyParser = require('body-parser');
const fs = require('fs');

const app = express();
const PORT = 3000; // Updated PORT variable

app.use(bodyParser.json());
app.use(express.static('public'));

app.post('/save-message', (req, res) => {
    const message = req.body.message;
    fs.appendFile('messages.txt', message + '\n', (err) => {
        if (err) {
            console.error('Error saving message:', err);
            res.status(500).json({ error: 'Error saving message' });
        } else {
            console.log('Message saved:', message);
            res.json({ message: 'Message saved' });
        }
    });
});

app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});
