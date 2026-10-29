const targetId = '%1';
const wins = workspace.windowList ? workspace.windowList() : workspace.clientList();

for (let i = 0; i < wins.length; ++i) {
    if (wins[i].internalId && wins[i].internalId.toString() === targetId) {
        wins[i].closeWindow();
        break;
    }
}