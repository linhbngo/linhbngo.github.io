---
layout: lecture
pretty_table: true
collection: csc496
course: CSC 496: iOS App Development
title: "SpriteKit"
toc:
  - name: SpriteKit
  - name: Create A New Example Game
  - name: Augment Your Game
  - name: Physics and Collision Detection
  - name: Properly end the game
---
# SpriteKit

## SpriteKit

{% details SpriteKit Framework %}

- Add a high-performance 2D content with smooth animtions to your app, 
or create a game with a high-levle set of 2D game-based tools

{% include figure.liquid path="assets/img/courses/csc496/09-sprite/01.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Create a New Project %}

- Start up XCode
    - Select `File\New\Project\...`, or
    - Select `New Project`
- Choose `iOS/Game` template and click `Next`

{% include figure.liquid path="assets/img/courses/csc496/09-sprite/02.png" width="50%" zoomable=true %}

- Enter `Pikachu` for `Product Name`
- Enter `Swift` for `Language`, 
- `SpriteKit` for `Game Technology`. 
- Select `None` for `Testing System`
- Make sure the option for Integrate GameplayKit is checked.

{% include figure.liquid path="assets/img/courses/csc496/09-sprite/03.png" width="50%" zoomable=true %}

- Select `iPhone 16` and start the simulation

{% include figure.liquid path="assets/img/courses/csc496/09-sprite/04.png" width="50%" zoomable=true %}

{% enddetails %}
## Create A New Example Game

{% details Setup %}

- Delete `GameScene.sks` and `Actions.sks`
- Make sure that `GameScene.swift` has only the followings:

```swift
import SpriteKit
import GameplayKit

class GameScene: SKScene {

    override func didMove(to view: SKView) {

    }
}
```

- Make sure that `GameViewController.swift` has the following contents:
    - This will force a landscape view when you launch your simulation. 

```swift
import UIKit
import SpriteKit
import GameplayKit

class GameViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
    }

    override var supportedInterfaceOrientations: UIInterfaceOrientationMask {
        return .landscape
    }

    override var prefersStatusBarHidden: Bool {
        return true
    }
}
```

{% enddetails %}
{% details View, Node, and Scene %}

- View (SKView)
    - The view is a bridge between SpriteKit and UIKit/AppKit.
    - It’s a subclass of UIView (iOS) or NSView (macOS) that renders SpriteKit content.
    - You use it to present scenes and to embed SpriteKit inside regular apps.
- Scene (SKScene)
    - A scene represents a self-contained 2D world or environment in your game.
    - It acts as the root node (container) for all visual content (sprites, labels, shapes, etc.).
    - You can think of a scene as a level or screen (e.g., main menu scene, gameplay scene, game over scene).
    - It handles input (like touches), updates (via update(_:)), and game logic.
- Node (SKNode)
    - A node is the basic building block for all elements in a scene.
    - Nodes can represent sprites (SKSpriteNode), labels (SKLabelNode), shapes, sounds, etc.
    - Nodes form a tree structure (scene graph), where each node can have children and a parent.
    - This structure makes it easy to move or transform groups of related nodes together.
- Analogy:
    - View: TV screen
    - Scene: The movie/episode playing on TV
    - Node: Actors and prop

{% enddetails %}
{% details Create your first scene %}


- Inside `GameViewController.swift`/`viewDidLoad()`, edit the function with the followings:

```swift
override func viewDidLoad() {
    super.viewDidLoad()
    //create the view
    if let view = self.view as! SKView? {
        //create the scene
        let scene = GameScene(size: CGSize(width: 1336, height: 1024))

        //set the scale mode to scale to fill the view window
        scene.scaleMode = .aspectFill

        //set the background colo
        scene.backgroundColor = UIColor(red: 105/255, green: 157/255, blue: 181/255, alpha: 1.0)

        //present the scene
        view.presentScene(scene)

        //set the view options
        view.ignoresSiblingOrder = false
        view.showsPhysics = false
        view.showsFPS = true
        view.showsNodeCount = true
    }
}
```

{% enddetails %}
{% details Creating your first visual node %}

- Recall: the SKNode class doesn’t render (draw) any visual content – it is 
considered the building block of SpriteKit because every node in a 
SpriteKit scene is a subclass of SKNode.
- To draw content, you need to use a visual node, such as:
    – SKSpriteNode: this node draws a rectangle texture, image or color.
    – SKShapeNode: Used along with a core graphics path to draw custom shapes.
    – SKLableNode: When you need text, this type of node is used to draw a text label
    – SKVideoNode: Display video content
    – SKReferenceNode: create reusable content
- Although the SKNode class does not allow for visual content, it does 
provide some standard properties that its subclasses inherit.
    – Position:
        - Frame
        - Position
        - zPosition
    – Scale and Rotation:
        - xScale
        - yScale
        - zRotation
- Download the following figures into your asset
    - [foreground](fig/09-sprite/foreground.png)
    - [background](fig/09-sprite/background.jpg)

- Edit function `didMove` in `GameScene.swift` to have the following contents

```swift
override func didMove(to view: SKView) {
    let background = SKSpriteNode(imageNamed: "background")
    background.anchorPoint = CGPoint(x:0, y:0)
    background.position = CGPoint(x:10, y:330)
    addChild(background)

    let foreground = SKSpriteNode(imageNamed: "foreground")
    foreground.anchorPoint = CGPoint(x: 0, y: 0)
    foreground.position = CGPoint(x: 15, y: 158)
    addChild(foreground)
}
```

{% include figure.liquid path="assets/img/courses/csc496/09-sprite/05.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Add a player %}

- Create a file named `SpriteKitHelper.swift` to set Z Position

```swift
import Foundation
import SpriteKit

enum Layer:CGFloat {
    case background
    case foreground
    case player
}
```

- Download and unzip the Pikachu image ([frame_0](codes/09-sprite/frame_0.zip)) and add it to the project's Asset.
- Create a new file called `Player.swift` with the following content:

```swift
import Foundation
import SpriteKit

class Player:SKSpriteNode {
    // MARK: - PROPERTIES

    // MARK: - INT
    init() {
        // set default textture
        let texture = SKTexture(imageNamed: "frame_0")

        // call to super.init
        super.init(texture: texture, color: .clear, size: texture.size())

        self.name = "player"
        self.setScale(1.0)
        self.anchorPoint = CGPoint(x: 0.5, y: 0.0)
        self.zPosition = Layer.player.rawValue
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}
```

- Ad player to the scene via `didMove` function in `GameScene`

```swift
let player = Player()
override func didMove(to view: SKView) {
    let background = SKSpriteNode(imageNamed: "background")
    background.anchorPoint = CGPoint(x:0, y:0)
    background.position = CGPoint(x:10, y:330)
    background.zPosition = Layer.background.rawValue
    addChild(background)

    let foreground = SKSpriteNode(imageNamed: "foreground")
    foreground.anchorPoint = CGPoint(x: 0, y: 0)
    foreground.position = CGPoint(x: 15, y: 158)
    foreground.zPosition = Layer.foreground.rawValue
    addChild(foreground)

    player.position = CGPoint(x: size.width/2, y: foreground.frame.maxY)
    addChild(player)
}
```

{% enddetails %}
{% details Add player movement %}


- Add the following function to `Player.swift`:

```swift
func moveToPosition(pos: CGPoint, speed: TimeInterval) {
    let moveAction = SKAction.move(to: pos, duration: speed)
    run(moveAction)
}
```

- Add the following functions and declaration to `GameScene.swift`

```swift
let player = Player()
```

```swift
func touchDown (atPoint pos: CGPoint) {
    player.moveToPosition(pos: pos, speed: 1.0)
}
```

```swift
override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
    for t in touches{self.touchDown(atPoint: t.location(in: self))}
}
```

- Attempt to use the mouse to move Pikachu along the way. 

{% enddetails %}
{% details Limit movement %}


- Add the following to Player.swift

```swift
func setupConstraints(floor: CGFloat) {
    let range = SKRange(lowerLimit: floor, upperLimit: floor)
    let lockToPlatform = SKConstraint.positionY(range)
    constraints = [lockToPlatform]
}
```

- Add the following to GameScene.swift below player.position statement

```swift
player.setupConstraints(floor: foreground.frame.maxY)
```

- Test the movement of Pikachu now.

{% enddetails %}
{% details Set movement direction %}


- Update `moveToPosition()` in Player.swift

```swift
func moveToPosition(pos: CGPoint, direction: String, speed: TimeInterval) {
    switch direction {
        case "L":
            xScale = -abs(xScale)
        default:
            xScale = abs(xScale)
    }
    let moveAction = SKAction.move(to: pos, duration: speed)
    run(moveAction)
}
```

- Update `touchDown()` in GameScene.swift

```swift
func touchDown (atPoint pos: CGPoint) {
    if pos.x < player.position.x {
        player.moveToPosition(pos: pos, direction: "L", speed: 1.0)
    } else {
        player.moveToPosition(pos: pos, direction: "R", speed: 1.0)
    }
}
```

{% enddetails %}
## Augment Your Game

{% details Add collectible item %}

- Download [fruit.png](codes/09-sprite/fruit.png) and drag the image into Assets. 
- Update `SpriteKitHelper.swift`

```swift
enum Layer:CGFloat {
    case background
    case foreground
    case player
    case collectible
}
```

- Create a file called `Collectible.swift` with the following contents

```swift
import Foundation
import SpriteKit

enum CollectibleType: String {
    case none
    case fruit
}

class Collectible: SKSpriteNode {
    private var collectibleType: CollectibleType = .none

    init(collectibleType: CollectibleType) {
        var texture: SKTexture!
        self.collectibleType = collectibleType

        //set the texture based on the Type
        switch self.collectibleType {
        case .fruit:
            texture = SKTexture(imageNamed: "fruit")
        case .none:
            break
        }
        super.init(texture: texture, color: SKColor.clear, size: texture.size())

        //set up the collectible
        self.name = "co_\(collectibleType)"
        self.anchorPoint = CGPoint(x: 0.5, y: 1.0)
        self.setScale(0.3)
        self.zPosition = Layer.collectible.rawValue
    }

    required init?(coder aDecoder: NSCoder){
        fatalError("init(coder:) has not been implemented")
    }
}
```

- Add the following function below `didMove()` inside GameScene.swift

```swift
func spawnFruit() {
    let collectible = Collectible(collectibleType: CollectibleType.fruit)
    collectible.position = CGPoint(x: player.position.x, y:player.position.y * 2.5)
    addChild(collectible)
}
```

- Add a call to spawnFruit() add the bottom of `didMove()`

```swift
    ...
    spawnFruit()
}
```

- Test that the fruit is visible in your game

{% enddetails %}
{% details Drop collectible item %}

- Add the following function to Collectible.swift below the initialization method

```swift
func drop(dropSpeed: TimeInterval, floorLevel: CGFloat) {
    let pos = CGPoint(x: position.x, y: floorLevel)
    let scaleX = SKAction.scaleX(to: 0.5, duration: 1)
    let scaleY = SKAction.scaleY(to: 0.5, duration: 1)
    let scale = SKAction.group([scaleX, scaleY])

    let appear = SKAction.fadeAlpha(to: 1, duration: 0.25)
    let moveAction = SKAction.move(to: pos, duration: dropSpeed)
    let actionSequence = SKAction.sequence([appear, scale, moveAction])

    self.scale(to: CGSize(width: 0.25, height: 1.0))
    self.run(actionSequence, withKey: "drop")
}
```

- Add the following line to the end of the `spawnFruit()` function inside GameScene.swift

```swift
collectible.drop(dropSpeed: TimeInterval(1.0), floorLevel: player.frame.minY)
```

- Test your game

{% enddetails %}
{% details Spawning fruits at random position %}


- Modify `spawnFruit()` function in GameScene.swift

```swift
func spawnFruit() {
    let collectible = Collectible(collectibleType: CollectibleType.fruit)

    //set random position
    let margin = collectible.size.width * 2
    let dropRange = SKRange(lowerLimit: frame.minX + margin, upperLimit: frame.maxX - margin)
    let randomX = CGFloat.random(in: dropRange.lowerLimit...dropRange.upperLimit)
    collectible.position = CGPoint(x: randomX, y:player.position.y * 2.5)
    addChild(collectible)
    collectible.drop(dropSpeed: TimeInterval(1.0), floorLevel: player.frame.minY)
}
```

- Run the game several times to test the random spawning. 

{% enddetails %}
{% details Spawning multiple fruits %}

- Add `spawnMultipleFruits()` in GameScene below `spawnFruit()`

```swift
func spawnMultipleFruits() {
    let wait = SKAction.wait(forDuration: TimeInterval(1.0))
    let spawn = SKAction.run {
        self.spawnFruit()
    }
    let sequence = SKAction.sequence([wait, spawn])
    let repeatAction = SKAction.repeat(sequence, count: 10)
    run(repeatAction, withKey: "fruit")
}
```

- Change `spawnFruit()` call in `didMove()` to `spawnMultipleFruits()`

{% enddetails %}
## Physics and Collision Detection

{% details Add physics body %}


- Add the following to 
    - the end of the `init()` function of Player.swift 
    - the end of the `init()` function of Collectible.swift

```
    ...
    // add physics body
    self.physicsBody = SKPhysicsBody(rectangleOf: self.size, center: CGPoint(x:0.0, y: self.size.height/2))
    self.physicsBody?.affectedByGravity = false
}
```

- Add physics to the foreground node (`didMove()` in GameScience.swift)

```swift
...
foreground.zPosition = Layer.foreground.rawValue
//add physics body
foreground.physicsBody = SKPhysicsBody(edgeLoopFrom: foreground.frame)
foreground.physicsBody?.affectedByGravity = false
foreground.physicsBody?.categoryBitMask = PhysicsCategory.foreground
foreground.physicsBody?.contactTestBitMask = PhysicsCategory.collectible
foreground.physicsBody?.collisionBitMask = PhysicsCategory.none
addChild(foreground)
...
```

- Add the following to SpriteKitHelper.swift

```swift
enum PhysicsCategory {
    static let none: UInt32 = 0 // a body that does not belong to any physics category
    static let player: UInt32 = 0b1 // 1: player objects
    static let collectible: UInt32 = 0b10 // 2: collectible objects
    static let foreground: UInt32 = 0b100 // 4: ground platforms or scenery that affects physics
}
```

- `PhysicsCategory` enumeration is a common pattern used in SpriteKit 
to define bitmask categories for physics bodies. 
- These bitmasks help managing
    - collision detection, 
    - contact notifications, and 
    - physics interactions between different types of objects in a game.
- Using binary (`0b...`) makes it visually clear that we are assigning 
non-overlapping bits. 
    - Each category should have its own unique bit so they can be combined using bitwise operations

{% enddetails %}
{% details Physics categories for foreground %}

- Add the following to the foreground section in `didMove()`

```swift
foreground.physicsBody?.categoryBitMask = PhysicsCategory.foreground // set category
foreground.physicsBody?.contactTestBitMask = PhysicsCategory.collectible //test collision with collectible
foreground.physicsBody?.collisionBitMask = PhysicsCategory.none
addChild(foreground)
...
```

{% enddetails %}
{% details Physics categories for player %}

- Add the following to `init()` of Player.swift

```swift
self.physicsBody?.categoryBitMask = PhysicsCategory.player // set category
self.physicsBody?.contactTestBitMask = PhysicsCategory.collectible //test collision with collectible
self.physicsBody?.collisionBitMask = PhysicsCategory.none
```

{% enddetails %}
{% details Physics categories for collectible %}

- Add the following to `init()` of Collectible.swift

```swift
self.physicsBody?.categoryBitMask = PhysicsCategory.collectible // set category
self.physicsBody?.contactTestBitMask = PhysicsCategory.player | PhysicsCategory.foreground //test collision with collectible
self.physicsBody?.collisionBitMask = PhysicsCategory.none
```

{% enddetails %}
{% details Detecting physical collision %}


- Add the following line to the beginning of the `didMove()` function in GameScene.swift
    - This declares that the GameScene class can act as a delegate for SKPhysicsContact Delegate and will respond to physics contact events. 

```swift
physicsWorld.contactDelegate = self
```

- Add an extension to handle colltions detection at the end of GameScene.swift (Outside of GameScence class)

```swift
extension GameScene: SKPhysicsContactDelegate {
    func didBegin(_ contact: SKPhysicsContact) {
        let collision = contact.bodyA.categoryBitMask | contact.bodyB.categoryBitMask

        if collision == PhysicsCategory.player | PhysicsCategory.collectible {
            print("player hit collectible")
        }

        if collision == PhysicsCategory.foreground | PhysicsCategory.collectible {
            print("collectible hit foreground")
        }
    }
}
```

- Test the game by checking the printed messages

{% enddetails %}
{% details Handling physical collision %}


- Add the following functions to Collectible.swift

```swift
func collected() {
    self.run(SKAction.removeFromParent())
}

func missed() {
    self.run(SKAction.removeFromParent())
}
```

- Modify the extension in GameScene.swift


```swift
func didBegin(_ contact: SKPhysicsContact) {
    let collision = contact.bodyA.categoryBitMask | contact.bodyB.categoryBitMask

    if collision == PhysicsCategory.player | PhysicsCategory.collectible {
        print("player hit collectible")
        let body = contact.bodyA.categoryBitMask == PhysicsCategory.collectible ? contact.bodyA.node : contact.bodyB.node

        if let sprite = body as? Collectible {
            sprite.collected()
        }
    }

    if collision == PhysicsCategory.foreground | PhysicsCategory.collectible {
        print("collectible hit foreground")
        let body = contact.bodyA.categoryBitMask == PhysicsCategory.collectible ? contact.bodyA.node : contact.bodyB.node

        if let sprite = body as? Collectible {
            sprite.missed()
        }
    }
}
```

- Add scoreLevel to class GameScene

```swift
var scoreLevel: SKLabelNode = SKLabelNode()
```

- Add `case ui` to `enum Layer` in SpriteKitHelper.swift
- Add a new method called `setupLabels()` to GameScene.swift

```swift
func setupLabels() {
    scoreLevel.name = "score"
    scoreLevel.fontColor = .black
    scoreLevel.fontSize = 55.0
    scoreLevel.horizontalAlignmentMode = .right
    scoreLevel.verticalAlignmentMode = .center
    scoreLevel.zPosition = Layer.ui.rawValue
    scoreLevel.position = CGPoint(x: frame.maxX - 50, y: 700)
    scoreLevel.text = "Score: 0"
    addChild(scoreLevel)
}
```

- Call `setupLabels()` after `spawnMultipleFruits()`
- Add a score variable to GameScene class to keep score

```swift
var score : Int = 0 {
    didSet {
        scoreLevel.text = "Score: \(score)"
    }
}
```

- Update score when player `collides` with collectible
    - Where do you think this should be placed?

```swift
score += 10
```

{% enddetails %}
## Properly end the game

{% details Game Over %}

- Add a `gameOver()` function to GameScene

```swift
func gameOver() {
    removeAction(forKey: "fruit")

    // loop through child nodes and stop actions on collectibles
    enumerateChildNodes(withName: "//co_*") {
        (node, stop) in
        node.removeAction(forKey: "drop")
        node.physicsBody = nil
    }

    let restartButton = SKSpriteNode(color: .blue, size: CGSize(width: 120, height:60))
    restartButton.name = "restartButton"
    restartButton.zPosition = Layer.ui.rawValue
    addChild(restartButton)

    let buttonText = SKLabelNode(text: "Restart")
    buttonText.fontColor = .white
    buttonText.fontSize = 30
    buttonText.verticalAlignmentMode = .center
    restartButton.addChild(buttonText)
}
```

- Add variables `missedCount` and `maxAllowedMisses` to GameScene class
    - Where to add?

```swift
var missedCount = 0
var maxAllowedMisses = 5
```

- Update function `didBegin()` in extension GameScene:SKPhysicsContactDelegate

```swift
if collision == PhysicsCategory.foreground | PhysicsCategory.collectible {
    print("collectible hit foreground")
    let body = contact.bodyA.categoryBitMask == PhysicsCategory.collectible ? contact.bodyA.node : contact.bodyB.node

    if let sprite = body as? Collectible {
        sprite.missed()
        missedCount += 1
        if missedCount >= maxAllowedMisses {
            gameOver()
        }
    }
}    
```

- Add function `restartGame()` to GameScene

```swift
func restartGame() {
    score = 0
    missedCount = 0
    enumerateChildNodes(withName: "//co_*") { (node, _) in node.removeFromParent()
    }

    enumerateChildNodes(withName: "restartButton") { (node, _) in
        node.removeFromParent()
    }
}
```

- Update `touchesBegin() function in GameScene to support button press

```swift
override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
    for t in touches{
        let location = t.location(in: self)
        let nodes = nodes(at: location)

        if nodes.contains(where: { $0.name == "restartButton"}) {
            //restart game
            restartGame()
        } else {
            self.touchDown(atPoint: t.location(in: self))
        }
    }
}
```

- Modify `spawnMultipleFruits` to support restart after a game successfully ended. 
    - **This is not working properly yet, no need to implement**

```swift
func spawnMultipleFruits() {
    let wait = SKAction.wait(forDuration: TimeInterval(1.0))
    let spawn = SKAction.run {
        self.spawnFruit()
    }
    let sequence = SKAction.sequence([wait, spawn])
    let repeatAction = SKAction.repeat(sequence, count: 10)
    let gameOverAction = SKAction.run {
            self.gameOver()
    }

    let fullSequence = SKAction.sequence([repeatAction, gameOverAction])
    run(fullSequence, withKey: "fruit")
}
```
{% enddetails %}
