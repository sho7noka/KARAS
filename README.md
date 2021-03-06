# [Merops](https://github.com/sho7noka/Merops)

[English](https://translate.google.com/translate?sl=ja&tl=en&u=https://github.com/sho7noka/Merops)(Google Translate)

Merops は `Apple Metal２2` と `Git`、`PixarUSD` をベースにした、次世代DCCツールの実験プロジェクトです。

## Concept
シンプル、早い、イテレーションの3軸が基本です。
- Metal2 ベースの Viewport と Modifier (OpenGL deprecate)
- 中ボタンを使わないウィジェットを極力排したジェスチャ、ゲーム画面に近い使用感
- [Pixar USD](https://github.com/PixarAnimationStudios/USD) と [libgit2](https://github.com/libgit2/objective-git) によるアセットパイプラインとイテレーションを重視

## Why?
1. 3Dソフトの操作は難しく複雑です。中ボタンクリックの多用を回避してシンプルな操作感を実現します。
2. [macOS design](https://developer.apple.com/design/human-interface-guidelines/macos/overview/themes/) や iOS に最適化されたDCCアプリケーションは数少ないのでそこを中心に据えます。
3. 入出力フォーマットで USDZ に対応します。XR、モバイルのコンテンツ制作連携に特化したツールを目標に開発を進めます。

### Author
[sho7noka](mailto:shosumioka@gmail.com)

### Contribute
[Contribute](../Contribute.md) を一読ください。

### License
[BSD](../License.md) ライセンスです。


## TODO
他のソフトのコンテクストを参考に実装を進めていますが統合ソフトは目指しません。

### Editor
- [ ] [point, line, face の DrawOverrideを選択オブジェクトから作る](x-source-tag://DrawOverride)
- [ ] [primitive選択の実現](https://github.com/metal-by-example/metal-picking) 
- [ ] 背景とグリッドを描画 /[カメラコントロールを同期](https://developer.apple.com/videos/play/wwdc2017/604/?time=789) /設定画面を表示
- [x] マウスイベントの両立
- [x] [libgit2でcommitとrevert](x-source-tag://libgit)
- [x] [TextField からオブジェクトの状態を変更](x-source-tag://TextField)
- [x] [subview 3Dコントローラー](x-source-tag://addSubView) ~~[bug](https://stackoverflow.com/questions/47517902/pixel-format-error-with-scenekit-spritekit-overlay-on-iphone-x) SpriteKit で 透明 HUD の描画~~
- [x] Blender like な [imgui Slider](https://github.com/mnmly/Swift-imgui) の実装
- [x] ~~PyRun_SimpleStringFlags と PyObjC の [GIL 回避](x-source-tag://gil)~~ Swift SIL を ctypes から [ios python](https://qiita.com/Hiroki_Kawakami/items/830baa5adcce5e483764)
- [x] [mouseEvent/TouchEvent](https://qiita.com/RichQiitaJp/items/79a52c55c9762b60f292) と Float をマルチプラットフォーム化
- [x] ~~WebKit View への書き込みと読み込み~~ vscode や vim に外部化

### Engine
- [x] [Rendererの分離](x-source-tag://engine)
- [ ] [arm64 USD](https://github.com/lighttransport/USD-android) を組み込む / [USDKit](https://github.com/jacques-gasselin/usdview-native)
- [ ] interpolation を [simdベースに](https://developer.apple.com/videos/play/wwdc2018/701/) 
- [ ] Metal2 でモディファイヤ テッセレーションとリダクション + ml/noise/lattice/edit 
- [ ] Model I/O で書き出せないgeometryとマテリアル以外を後変更
- [ ] Server から GET/POST

### Research
- [tensorflow lite](https://medium.com/tensorflow/tensorflow-lite-now-faster-with-mobile-gpus-developer-preview-e15797e6dee7)
- [iPadPro compatible with pencil](https://developer.apple.com/videos/play/wwdc2016/220/)

## Developper 向け

```bash
python build.py
```

```bash
carthage update --verbose --no-use-binaries --use-ssh
```

https://github.com/libgit2/objective-git/blob/master/README.md


### [Debug](https://developer.apple.com/videos/play/wwdc2018/608/)

1. [スキーマ](https://cocoaengineering.com/2018/01/01/some-useful-url-schemes-in-xcode-9/)

2. [break point](https://qiita.com/shu223/items/1e88d19fbb31298146ca)
先に以下の設定が必要。
`Build Settings > Produce Debuging Infomation > YES, include source code`

- [Show Debug the navigator] タブの [FPS] をクリック
- [dependency viewer](https://developer.apple.com/documentation/metal/tools_profiling_and_debugging/seeing_a_frame_s_render_passes_with_the_dependency_viewer)
    - [Show Debug the Navigator] タブ > [View Frame By Call] を選択
- geometry viewer
    - [Capture GPU Frame] を押す
- shader debugger
    - [Debug Shader] > [Debug] の順で押す
- enhanced shader profiler
    - A11 を搭載した実機でのみ確認可能

3. キャプチャ、ラベル、グループ
```swift
renderCommandEncoder.label = "hoge"

// capture
MTLCaptureManager.shared().startCapture(device: device)
// ~~
MTLCaptureManager.shared().stopCapture()

// group
renderCommandEncoder.pushDebugGroup("hoge")
// ~~
renderCommandEncoder.popDebugGroup()
```

### snippets
```swift
metalLayer = self.layer as? CAMetalLayer
if let drawable = metalLayer.nextDrawable()

// https://developer.apple.com/documentation/scenekit/scnnode/1407998-hittestwithsegment
child.hitTestWithSegment(from: <#T##SCNVector3#>, to: <#T##SCNVector3#>, options: <#T##[String : Any]?#>)

func degreesToRadians(_ degrees: Float) -> Float {
return degrees * .pi / 180
}

let sceneKitVertices = vertices.map {
let cube = newNode.flattenedClone()
cube.simdPosition = SCNVector3(x: $0.x, y: $0.y, z: $0.z)
return cube
}

// scenekit で頂点作るパターン
1. ジオメトリから simd vertex position を取得する
2. cube を配置する

scene.rootNode.replaceChildNode(<#T##oldChild: SCNNode##SCNNode#>, with: <#T##SCNNode#>)

let vector:[Float] = [0,1,2,3,4,5,6,7,8,9]   
let byteLength = arr1.count*MemoryLayout<Float>.size
let buffer = metalDevice.makeBuffer(bytes: &vector, length: byteLength, options: MTLResourceOptions())
let vector2:[Float] = [10,20,30,40,50,60,70,80,90]

buffer.contents().copyBytes(from: vector2, count: vector2.count * MemoryLayout<Float>.stride)
```

https://qiita.com/lumis/items/311b8c39d61312957195
https://qiita.com/mss634/items/170d3cb401eee4ec1253
https://stackoverflow.com/questions/15470367/pyeval-initthreads-in-python-3-how-when-to-call-it-the-saga-continues-ad-naus]

https://gist.github.com/rikner/2f2677c56d1adef277d03bdb322eca80
