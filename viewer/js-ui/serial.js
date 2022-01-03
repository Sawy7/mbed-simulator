(function() {
    var terminal = new Terminal({
        scrollback: 1000000
    });
    const fitAddon = new FitAddon.FitAddon();
    terminal.loadAddon(new WebLinksAddon.WebLinksAddon());
    terminal.loadAddon(fitAddon);
    terminal.open(document.querySelector('#output'));
    fitAddon.fit();
    window.terminal = terminal;

    window.MbedJSHal.serial.on('stdout', function(c) {
        if (typeof c === 'number') {
            c = String.fromCharCode(c);
        }
        // used to communicate back to Puppeteer (see cli.js)
        if (typeof window.onPrintEvent === 'function') {
            window.onPrintEvent(c);
        }

        // should be handled by Mbed OS, but it isn't...
        if (c === '\n') {
            terminal.write('\r');
        }

        terminal.write(c);
    });

    window.MbedJSHal.serial.on('stdout-line', function(l) {
        if (typeof window.onPrintEvent === 'function') {
            window.onPrintEvent(l);
        }

        terminal.write(l);
    });

    window.addEventListener('keypress', function(e) {
        window.MbedJSHal.serial.onStdIn(e.charCode);
    });
})();
