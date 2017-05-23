import "../style/index.scss";

function initialize() {
    let availability = WebDNN.getBackendAvailability();

    for (let backend of ['webgpu', 'webassembly', 'fallback']) {
        for (let node of Array.from(document.querySelectorAll(`.Compatibility-${backend}.Compatibility-checking`))) {
            node.classList.remove('Compatibility-checking');
            let statusNode = node.querySelector('.Compatibility-Status');

            if (availability.status[backend]) {
                node.classList.add('Compatibility-supported');
                if (statusNode) statusNode.textContent = 'Supported';
            } else {
                node.classList.add('Compatibility-not_supported');
                if (statusNode) statusNode.textContent = 'Not supported';
            }
        }
    }
}
window.onload = initialize;