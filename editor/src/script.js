document.addEventListener('DOMContentLoaded', function () {
    const gravityCode = document.getElementById('gravity-code');
    const output = document.getElementById('output');
    const runBtn = document.getElementById('run-btn');
    const increaseFontBtn = document.getElementById('increase-font');
    const decreaseFontBtn = document.getElementById('decrease-font');
    const fullscreenBtn = document.getElementById('fullscreen-btn');
    const exitFullscreenBtn = document.getElementById('exit-fullscreen-btn');
    const lineNumbers = document.getElementById('line-numbers');
    const loadingContainer = document.getElementById('loading-container');
    const codeEditor = document.querySelector('.code-editor');
    const errorMessage = document.getElementById('error-message');
    const tryAgainButton = document.getElementById('try-again-button');

    // Simulate loading sequence
    setTimeout(() => {
        loadingContainer.classList.add('hidden');
        document.body.style.overflow = 'auto';
    }, 2000);

    // WebSocket connection
    const socket = new WebSocket('ws://localhost:8765'); // Replace with your WebSocket server URL

    // Handle WebSocket connection open
    socket.addEventListener('open', () => {
        console.log('WebSocket connection established');
        if (errorMessage) errorMessage.classList.add('hidden'); // Hide error if connection succeeds
        clearTimeout(connectionTimeout); // Clear failure detection timeout
    });

    // Handle WebSocket messages (server responses)
    socket.addEventListener('message', (event) => {
        const response = JSON.parse(event.data); // Parse the server response
        if (response.output) {
            output.srcdoc = `
                <html>
                    <head>
                        <link rel="stylesheet" href="../src/styles/styles.css">
                    </head>
                    <body class="iframe-styles">
                        <pre id="pre-text"></pre>
                        <script>
                            document.getElementById("pre-text").textContent = \`${response.output}\`;
                        </script>
                    </body>
                </html>
            `;
        } else {
            console.error('Invalid response from server:', response);
        }
    });

    // Handle WebSocket errors
    socket.addEventListener('error', () => {
        console.error('WebSocket error occurred');
        showError();
    });

    // Handle WebSocket connection close
    socket.addEventListener('close', (event) => {
        console.warn('WebSocket connection closed:', event);
        showError();
    });

    // Function to show error message
    function showError() {
        if (errorMessage) {
            console.warn('Displaying error message.');
            errorMessage.classList.remove('hidden'); // Show error message
            errorMessage.style.display = 'block'; // Ensure it's visible
        } else {
            console.warn('Error message element not found.');
        }
    }

    // Detect if the WebSocket connection fails silently
    const connectionTimeout = setTimeout(() => {
        if (socket.readyState !== WebSocket.OPEN) {
            console.warn('WebSocket connection failed (timeout)');
            showError();
        }
    }, 3000); // Wait 3 seconds before assuming failure

    // Try Again button click event
    tryAgainButton.addEventListener('click', () => {
        window.location.reload(); // Refresh the page
    });

    // Function to send code to the server
    function sendCodeToServer() {
        const code = gravityCode.value;
        if (code.trim() === '') {
            alert('Please write some code before running.');
            return;
        }
        socket.send(JSON.stringify({ code }));
    }

    // Run button click event
    runBtn.addEventListener('click', sendCodeToServer);

    // Font size controls
    let fontSize = 18;
    const minFontSize = 12;
    const maxFontSize = 24;

    increaseFontBtn.addEventListener('click', () => {
        if (fontSize < maxFontSize) {
            fontSize += 2;
            gravityCode.style.fontSize = `${fontSize}px`;
            updateLineNumbers();
        }
    });

    decreaseFontBtn.addEventListener('click', () => {
        if (fontSize > minFontSize) {
            fontSize -= 2;
            gravityCode.style.fontSize = `${fontSize}px`;
            updateLineNumbers();
        }
    });

    // Full-screen button click event
    fullscreenBtn.addEventListener('click', () => {
        codeEditor.classList.add('fullscreen');
        fullscreenBtn.style.display = 'none';
        exitFullscreenBtn.style.display = 'block';
    });

    // Exit full-screen button click event
    exitFullscreenBtn.addEventListener('click', () => {
        codeEditor.classList.remove('fullscreen');
        exitFullscreenBtn.style.display = 'none';
        fullscreenBtn.style.display = 'inline-flex';
    });

    // Update line numbers
    function updateLineNumbers() {
        const lines = gravityCode.value.split('\n').length;
        lineNumbers.innerHTML = Array.from({ length: lines }, (_, i) => i + 1).join('<br>');
    }

    // Throttle the updateLineNumbers function
    let isThrottled = false;
    gravityCode.addEventListener('input', () => {
        if (!isThrottled) {
            updateLineNumbers();
            isThrottled = true;
            setTimeout(() => {
                isThrottled = false;
            }, 100);
        }
    });

    // Initial update
    updateLineNumbers();
});