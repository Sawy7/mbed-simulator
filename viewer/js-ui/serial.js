window.xtermFitAddon = new FitAddon.FitAddon();
(function() {
    var terminal = new Terminal({
        scrollback: 1000000
    });
    terminal.loadAddon(new WebLinksAddon.WebLinksAddon());
    let xtermFitAddon = window.xtermFitAddon;
    terminal.loadAddon(xtermFitAddon);
    terminal.open(document.querySelector('#output'));
    xtermFitAddon.fit();
    window.terminal = terminal;

    window.addEventListener('load', function(){
        document.getElementById('output').addEventListener('click', function() {
            if(window.xtermFitAddon !== undefined) {
                window.xtermFitAddon.fit();
            }
        }, false);
	const resizeObserver = new ResizeObserver(entries => {
	    for (let entry of entries) {
		if(entry.contentBoxSize) {
		    // Firefox implements `contentBoxSize` as a single content rect, rather than an array
		    const contentBoxSize = Array.isArray(entry.contentBoxSize) ? entry.contentBoxSize[0] : entry.contentBoxSize;		    
		} else {
		}
	    }
	    console.log('Terminal size changed');
	    window.xtermFitAddon.fit();
	});
	resizeObserver.observe(document.getElementById('output'));
    }, false);
    
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
