/// <reference path="../libs/webdnn.d.ts" />
/// <reference path="../libs/webcamjs.d.ts" />
import "../style/neural_style_transfer.scss";
import InitializingView from "./modules/initializing_view";

enum State {
    INITIALIZING,
    STAND_BY,
    RUNNING,
    ERROR,
}

const App = new class {
    runner: WebDNN.DescriptorRunner;
    inputView: Float32Array;
    outputView: Float32Array;
    inputCanvas: HTMLCanvasElement;
    inputCtx: CanvasRenderingContext2D;
    outputCtx: CanvasRenderingContext2D;
    runButton: HTMLButtonElement;
    state: State = State.INITIALIZING;
    w: number;
    h: number;

    async initialize() {
        let runButton = document.getElementById('runButton') as HTMLButtonElement;
        if (!runButton) throw Error('#runButton is not found.');
        this.runButton = runButton;
        this.runButton.addEventListener('click', () => App.onPlayButtonClick());

        let launchView = document.getElementById('launchView');
        if (launchView && launchView.parentNode) {
            launchView.parentNode.removeChild(launchView);
            launchView = null;
        }

        let initializingViewBase = document.getElementById('initializingView');
        if (!initializingViewBase) throw Error('#initializingView is not found');
        let initializingView = new InitializingView(initializingViewBase);

        initializingView.updateMessage('Load model data');

        await WebDNN.init();
        this.runner = WebDNN.gpu.createDescriptorRunner();
        await this.runner.load('./models/neural_style_transfer', (loaded, total) => initializingView.updateProgress(loaded / total));
        this.inputView = (await this.runner.getInputViews())[0];
        this.outputView = (await this.runner.getOutputViews())[0];

        initializingView.remove();

        let inputCanvas = document.getElementById('inputCanvas') as HTMLCanvasElement;
        if (!inputCanvas) throw Error('#inputCanvas is not found');
        this.inputCanvas = inputCanvas;
        this.w = inputCanvas.width;
        this.h = inputCanvas.height;

        let inputCtx = inputCanvas.getContext('2d');
        if (!inputCtx) throw Error('Canvas initialization failed');
        this.inputCtx = inputCtx;

        let outputCanvas = document.getElementById('outputCanvas') as HTMLCanvasElement;
        if (!outputCanvas) throw Error('#outputCanvas is not found');

        let outputCtx = outputCanvas.getContext('2d');
        if (!outputCtx) throw Error('Canvas initialization failed');
        this.outputCtx = outputCtx;

        Webcam.set({
            width: 192,
            height: 144,
            fps: 60,
            flip_horiz: true,
            image_format: 'png',
            force_flash: false
        });
        Webcam.on('error', (err) => {
            console.error(err);
            this.setState(State.ERROR);
        });
        Webcam.on('live', () => {
            this.setState(State.STAND_BY);
        });
        Webcam.attach('#CameraContainer');
    }

    onPlayButtonClick() {
        switch (this.state) {
            case State.STAND_BY:
                this.setState(State.RUNNING);
                break;

            case State.RUNNING:
                this.setState(State.STAND_BY);
                break;

            default:
                break;
        }
    }

    setState(state: State) {
        switch (state) {
            case State.INITIALIZING:
                this.runButton.textContent = 'Initializing...';
                this.runButton.disabled = true;
                break;

            case State.STAND_BY:
                this.runButton.textContent = 'Run';
                this.runButton.disabled = false;
                break;

            case State.RUNNING:
                this.runButton.textContent = 'Stop';
                this.runButton.disabled = false;
                this.transfer();
                break;

            case State.ERROR:
                this.runButton.disabled = true;
                break;
        }
        this.state = state;
    }

    async transfer() {
        await this.getImageData();

        await this.runner.run();
        this.setImageData();

        if (this.state == State.RUNNING) requestAnimationFrame(() => this.transfer());
    }

    async getImageData() {
        let w = this.w;
        let h = this.h;

        await new Promise(resolve => Webcam.snap(resolve, this.inputCanvas));
        let pixelData = this.inputCtx.getImageData(0, 0, w, h).data;

        for (let y = 0; y < h; y++) {
            for (let x = 0; x < w; x++) {
                this.inputView[(y * w + x) * 3] = pixelData[(y * w + x) * 4];
                this.inputView[(y * w + x) * 3 + 1] = pixelData[(y * w + x) * 4 + 1];
                this.inputView[(y * w + x) * 3 + 2] = pixelData[(y * w + x) * 4 + 2];
            }
        }
    }

    setImageData() {
        let w = this.w;
        let h = this.h;

        let imageData = new ImageData(w, h);

        for (let y = 0; y < h; y++) {
            for (let x = 0; x < w; x++) {
                imageData.data[(y * w + x) * 4] = this.outputView[(y * w + x) * 3];
                imageData.data[(y * w + x) * 4 + 1] = this.outputView[(y * w + x) * 3 + 1];
                imageData.data[(y * w + x) * 4 + 2] = this.outputView[(y * w + x) * 3 + 2];
                imageData.data[(y * w + x) * 4 + 3] = 255;
            }
        }

        this.outputCtx.putImageData(imageData, 0, 0);
    }

    async predict() {
        // let start = performance.now();
        // await this.runner.run();
        // let computationTime = performance.now() - start;
        //
        // let output: number[] = [];
        // for (let v of this.outputView) {
        //     output.push(v);
        // }
        //
        // let top5 = WebDNN.Math.argmax(output, 5);
        // top5.forEach((labelId, i) => {
        //     this.predictedLabelViews[i].textContent = this.labels[labelId];
        // });
    }
};

window.addEventListener('DOMContentLoaded', () => {
    // WebDNN.registerFetchDelegate((input, init) => {
    //     let url = (typeof input == 'string') ? input : input.url;
    //     let ma = url.match(/resnet50\/(.+?).bin(?:\?.*)?$/);
    //
    //     if (ma) {
    //         return fetch(`https://media.githubusercontent.com/media/Kiikurage/demo-data/master/resnet50/${ma[1]}.bin`);
    //     } else {
    //         return fetch(input, init);
    //     }
    // });

    let runAppButton = document.getElementById('runAppButton');
    if (!runAppButton) throw Error('#runAppButton is not found');
    runAppButton.addEventListener('click', () => App.initialize());
});
