/// <reference path="../libs/webdnn.d.ts" />
import "../style/resnet50.scss";
import ImagePicker from "./modules/image_picker";
import InitializingView from "./modules/initializing_view";

const NUM_RANDOM_IMAGE = 3;

const App = new class {
    picker: ImagePicker;
    context: CanvasRenderingContext2D;
    runner: WebDNN.DescriptorRunner;
    inputView: Float32Array;
    outputView: Float32Array;
    runButton: HTMLButtonElement;
    firstMessageView: HTMLElement;
    resultView: HTMLElement;
    computationTimeView: HTMLElement;
    predictedLabelViews: HTMLElement[];
    labels: string[];
    randomImageIndex: number;

    async initialize() {
        this.randomImageIndex = Math.floor(Math.random() * NUM_RANDOM_IMAGE);

        let canvas = document.getElementById('canvas') as HTMLCanvasElement;
        let context = canvas.getContext('2d');
        if (!context) throw new Error('Context is null');

        this.context = context;
        this.picker = new ImagePicker(
            document.getElementById('imageInput') as HTMLInputElement, context
        );
        this.picker.onload = () => {
            this.runButton.disabled = false;
        };

        let runButton = document.getElementById('runButton') as HTMLButtonElement;
        if (!runButton) throw Error('#runButton is not found.');
        this.runButton = runButton;
        this.runButton.addEventListener('click', () => App.predict());

        let loadRandomButton = document.getElementById('loadRandomButton');
        if (!loadRandomButton) throw Error('#loadRandomButton is not found.');
        loadRandomButton.addEventListener('click', () => App.loadRandomImage());

        let firstMessageView = document.getElementById('firstMessage');
        if (!firstMessageView) throw Error('#firstMessageView is not found.');
        this.firstMessageView = firstMessageView;

        let resultView = document.getElementById('result');
        if (!resultView) throw Error('#result is not found.');
        this.resultView = resultView;

        let computationTimeView = document.getElementById('computationTime');
        if (!computationTimeView) throw Error('#computationTime is not found.');
        this.computationTimeView = computationTimeView;

        this.predictedLabelViews = [];
        for (let i = 0; i < 5; i++) {
            let predictedLabelView = document.getElementById(`predictedLabel${i}`);
            if (!predictedLabelView) throw Error(`#predictedLabelView${i} is not found.`);
            this.predictedLabelViews.push(predictedLabelView);
        }

        let launchView = document.getElementById('launchView');
        if (launchView && launchView.parentNode) {
            launchView.parentNode.removeChild(launchView);
            launchView = null;
        }

        let initializingViewBase = document.getElementById('initializingView');
        if (!initializingViewBase) throw Error('#initializingView is not found');
        let initializingView = new InitializingView(initializingViewBase);
        initializingView.updateMessage('Load label data');

        let labelData = await((await fetch(`./assets/synset_words.txt`)).text());
        this.labels = labelData.split('\n')
            .map(line => line.split(',')[0])
            .map(label => label.replace(/^n\d+\w+/g, '').toLowerCase());

        initializingView.updateMessage('Load model data');

        await WebDNN.init();
        this.runner = WebDNN.gpu.createDescriptorRunner();
        await this.runner.load('./models/resnet50', (loaded, total) => initializingView.updateProgress(loaded / total));
        this.inputView = (await this.runner.getInputViews())[0];
        this.outputView = (await this.runner.getOutputViews())[0];

        initializingView.remove();
    }

    setInputImageData() {
        let w = this.context.canvas.width;
        let h = this.context.canvas.height;
        let imageData = this.context.getImageData(0, 0, w, h);
        let pixelData = imageData.data;

        for (let y = 0; y < h; y++) {
            for (let x = 0; x < w; x++) {
                this.inputView[(y * w + x) * 3] = pixelData[(y * w + x) * 4 + 2] - 103.939;
                this.inputView[(y * w + x) * 3 + 1] = pixelData[(y * w + x) * 4 + 1] - 116.779;
                this.inputView[(y * w + x) * 3 + 2] = pixelData[(y * w + x) * 4] - 123.68;
            }
        }
    }

    loadRandomImage() {
        this.randomImageIndex = (this.randomImageIndex + 1) % NUM_RANDOM_IMAGE;
        this.picker.loadByUrl(`./assets/images/${this.randomImageIndex}.png`);
    }

    async predict() {
        this.setInputImageData();

        let start = performance.now();
        await this.runner.run();
        let computationTime = performance.now() - start;

        let output: number[] = [];
        for (let v of this.outputView) {
            output.push(v);
        }

        let top5 = WebDNN.Math.argmax(output, 5);
        top5.forEach((labelId, i) => {
            this.predictedLabelViews[i].textContent = this.labels[labelId];
        });

        this.firstMessageView.style.display = 'none';
        this.resultView.style.display = '';
        this.computationTimeView.textContent = computationTime.toFixed(2);
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
