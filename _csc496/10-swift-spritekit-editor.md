---
layout: lecture
pretty_table: true
collection: csc496
title: "SpriteKit: Scene Editor"
toc:
  - name: Preparation
  - name: Using Scene Editor to Add Nodes
  - name: Hands-on Exercise
---
# SpriteKit: Scene Editor

## Preparation

{% details Download assets %}

- Download and unzip the following files
    - [Pokemon2D Assets 1](codes/10-sprite-editor/Pokemon2D_Assets_1.zip)
    - [Pokemon2D Assets 2](codes/10-sprite-editor/Pokemon2D_Assets_2.zip)
- Unzip
- We will drag the assets into XCode as needed. 

{% enddetails %}
{% details SpriteKit Scene Editor %}

- A built-in feature of Xcode that allows us to create SpriteKit nodes 
and assign values to them. 

{% enddetails %}
{% details Create a New Project %}

- Start up XCode
    - Select `File\New\Project\...`, or
    - Select `New Project`
- Choose `iOS/Game` template and click `Next`
    - **Do not choose Multiplatform**

{% include figure.liquid path="assets/img/courses/csc496/10-sprite-editor/01.png" width="50%" zoomable=true %}

- Enter `Pokemon2D` for `Product Name`
- Enter `Swift` for `Language`, 
- `SpriteKit` for `Game Technology`. 
- Select `None` for `Testing System`
- Make sure the option for Integrate GameplayKit is checked.

{% include figure.liquid path="assets/img/courses/csc496/10-sprite-editor/02.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Clean up default template %}

- Delete `Actions.sks`
- Make sure that `GameScene.swift` has only the followings:

```swift
import SpriteKit
import GameplayKit

class GameScene: SKScene {

    var entities = [GKEntity]()
    var graphs = [String : GKGraph]()

    private var lastUpdateTime : TimeInterval = 0

    override func sceneDidLoad() {

        self.lastUpdateTime = 0

    }

    func touchDown(atPoint pos : CGPoint) {
    }

    func touchMoved(toPoint pos : CGPoint) {
    }

    func touchUp(atPoint pos : CGPoint) {
    }

    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        for t in touches { self.touchDown(atPoint: t.location(in: self)) }
    }

    override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?) {
        for t in touches { self.touchMoved(toPoint: t.location(in: self)) }
    }

    override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?) {
        for t in touches { self.touchUp(atPoint: t.location(in: self)) }
    }

    override func touchesCancelled(_ touches: Set<UITouch>, with event: UIEvent?) {
        for t in touches { self.touchUp(atPoint: t.location(in: self)) }
    }
}
```


{% enddetails %}
{% details Adding Assets %}

- Unzip `Pokemon2D_Assets_1.zip` and drag the **files** into `Assets`

{% include figure.liquid path="assets/img/courses/csc496/10-sprite-editor/add_assets_01.png" width="50%" zoomable=true %}

{% enddetails %}
## Using Scene Editor to Add Nodes

{% details Set deployment environment %}


- `Scene`: Size is iPad 12.9"
- Portrait Mode

{% enddetails %}
{% details Adding your first node %}

- Select `GameScene.sks`
- Remove the existing node, `helloLabel`

{% include figure.liquid path="assets/img/courses/csc496/10-sprite-editor/removeHello.png" width="50%" zoomable=true %}

- Click the “+” sign
- Drag and drop the “Color Sprite” to the Scene

{% include figure.liquid path="assets/img/courses/csc496/10-sprite-editor/addSprite.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Modifying your node %}


{% include figure.liquid path="assets/img/courses/csc496/10-sprite-editor/newSprite_default_background.png" width="50%" zoomable=true %}

- Click on `Textture` and select `background_grass`
    - Set X and Y positions to 0 and 0

{% include figure.liquid path="assets/img/courses/csc496/10-sprite-editor/newSprite_grass.png" width="50%" zoomable=true %}

- Run the simulator to test

{% enddetails %}
{% details Locking your node %}


- Right click the SKSpriteNode (background) and lock it. 

{% include figure.liquid path="assets/img/courses/csc496/10-sprite-editor/lockSprite.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Adding control buttons %}


- Add an Empty node
    - Make sure you set the zPosition to 1 (above zPosition 0 of the background_grass)

{% include figure.liquid path="assets/img/courses/csc496/10-sprite-editor/nodeEmpty.png" width="50%" zoomable=true %}

- Add for more "Color Sprite" to the Scene and drag them under the SKNode
    - This is to group the up. 

{% include figure.liquid path="assets/img/courses/csc496/10-sprite-editor/groupNodes.png" width="50%" zoomable=true %}


- Change the texture of all four Color Sprite Nodes to `arrow`
    - adjust the size and rotation to make it like an on-screen controller (directional pad, aka D-Pad)

{% include figure.liquid path="assets/img/courses/csc496/10-sprite-editor/dpad.png" width="50%" zoomable=true %}

- Add another color sprite node, place it in the middle of the dpad and change the texture `player_back`. 

{% include figure.liquid path="assets/img/courses/csc496/10-sprite-editor/controller_stop.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Add player node %}


- Add another Color Sprite Node (the player) and change the texture to `player_up`. 
You can adjust the size if you want.
    - Make sure you set the zPosition to 1 (above zPosition 0 of the background_grass)

{% include figure.liquid path="assets/img/courses/csc496/10-sprite-editor/playerNode.png" width="50%" zoomable=true %}

- Change the `name` of the dpad buttons to `controller_up`, `controller_down`, `controller_left`, 
and `controller_right` accordingly. 

{% include figure.liquid path="assets/img/courses/csc496/10-sprite-editor/dpad_names.png" width="50%" zoomable=true %}

- Click the Player node, change the `Body Type` to Bounding Circle, select `Dynamic` and 
deselect the allows rotation and affected by gravity options.
- Change Fraction, restitution, Lin. Damping and Ang. damping to 0.
- Set Category mask to 1, collision mask to 0, the field mask to 0 and the contact mask to 0

{% include figure.liquid path="assets/img/courses/csc496/10-sprite-editor/nodePlayer_2.png" width="50%" zoomable=true %}

- Run the game once to test/confirm

{% include figure.liquid path="assets/img/courses/csc496/10-sprite-editor/test_ipad.png" width="50%" zoomable=true %}

- Create a Player class (`Player.swift`) with the following codes

```swift
import Foundation
import SpriteKit

enum Direction: String {
    case stop
    case left
    case right
    case up
    case down
}

class Player: SKSpriteNode {
    func move(_ direction: Direction) {
        print("player move: \(direction.rawValue)")
    }

    func stop() {
        print("Stop")
    }
}
```

- Assign Player node to Player class using Custom Class

{% include figure.liquid path="assets/img/courses/csc496/10-sprite-editor/nodeCustomPlayer.png" width="50%" zoomable=true %}


{% enddetails %}
{% details Test player movement %}


- Modify this section of `GameScene.swift`

```swift
...
private var lastUpdateTime : TimeInterval = 0
private var player: Player?

override func sceneDidLoad() {
    self.lastUpdateTime = 0
}

override func didMove(to view: SKView) {
    player = childNode(withName: "player") as? Player
    player?.move(.stop)
}

func touchDown(atPoint pos : CGPoint) {
    print("touch down")
    let nodeAtPoint = atPoint(pos)
    if let touchedNode = nodeAtPoint as? SKSpriteNode{
        if touchedNode.name?.starts(with: "controller_") == true{
            let direction = touchedNode.name?.replacingOccurrences(of: "controller_", with: "")
            player?.move(Direction(rawValue: direction ?? "stop")!)
        }
    }
}
...
```

- Run and test movement (based on the print statement)

{% include figure.liquid path="assets/img/courses/csc496/10-sprite-editor/testMovement.png" width="50%" zoomable=true %}

- Modify functions `move` and `stop` inside class `Player` with the following contents. 

```swift
func move(_ direction: Direction) {
    print("player move: \(direction.rawValue)")
    switch direction {
    case .up:
        self.physicsBody?.velocity = CGVector(dx: 0, dy: 100)
    case .down:
        self.physicsBody?.velocity = CGVector(dx: 0, dy: -100)
    case .left:
        self.physicsBody?.velocity = CGVector(dx: -100, dy: 0)
    case .right:
        self.physicsBody?.velocity = CGVector(dx: 100, dy: 0)
    case .stop:
        stop()
    }
}

func stop() {
    print("Stop")
    self.physicsBody?.velocity = CGVector(dx: 0, dy: 0)
}
```

- Rerun the simulation and observe the movements of the player node. 

{% enddetails %}
## Hands-on Exercise

{% details Preparation %}


- Unzip `Pokemon2D_Assets_2.zip` and drag the **files** into `Assets`

{% enddetails %}
{% details Tasks %}


- Add a new node, `tree`,  to the game (from the assets).
- Use multiple tree nodes to create a maze that the player cannot pass through.
    - Hint: Set the Category Mask and Collision Mask for both the player and 
    the tree node.
- Add a Pokémon node (node name: `pokemon`), and when the player hits the
Pokémon, it will print "Player hit the Pokémon" in the console.

- You will need to set up `contactDelegate` and `SKPhysicsContactDelegate` 
{% enddetails %}
