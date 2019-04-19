# WebDNN Webpage Data Files

# resnet50
`webdnn/examples/resnet50`を使用。

```
python convert_resnet_keras.py --encoding eightbit --backend webgpu,webgl,webassembly
```

で生成した`output_keras`ディレクトリをコピー。

# neural_style_transfer
`webdnn/examples/neural_style_transfer`を使用。

```
python convert.py --encoding eightbit --backend webgpu
python convert.py --encoding eightbit --backend webgl
python convert.py --encoding eightbit --backend webassembly
```

で生成。`output`ディレクトリをコピー。

# yolo9000
TODO

# squeeze_net
`webdnn/examples/squeeze_net`を使用。

```
python convert_keras.py --encoding eightbit --backend webgpu
python convert_keras.py --encoding eightbit --backend webgl
python convert_keras.py --encoding eightbit --backend webassembly
```

で生成。`output_keras`ディレクトリをコピー。
