function send(kind, win) {
    if (!win || !win.internalId) return;
    const id = win.internalId.toString();
    const title = win.caption || "";
    callDBus("%1", "%2", "%3", kind, id, title);
}

const addSignal = workspace.windowAdded || workspace.clientAdded;
const removeSignal = workspace.windowRemoved || workspace.clientRemoved;

if (addSignal) {
    addSignal.connect(function(w) { 
        send("onWindowOpened", w); 
    });
}

if (removeSignal) {
    removeSignal.connect(function(w) { 
        send("onWindowClosed", w); 
    });
}

const current = workspace.windowList ? workspace.windowList() : workspace.clientList();
for (let i = 0; i < current.length; ++i) {
    send("onWindowOpened", current[i]);
}