---
layout: lecture
pretty_table: true
collection: csc496
course: CSC 496: iOS App Development
title: "SpriteKit: Scene Editor"
toc:
  - name: Preparation
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
{% details Create Health Component %}

- Create a new file called `HPComponent.swift`

```swift
import SpriteKit
import GameplayKit

class HPComponent: GKComponent {

    override func didAddToEntity() {
        guard let node = entity?.component(ofType: GKSKNodeComponent.self)?.node
        else {
            return
        }
        if let HPMeter = SKReferenceNode(fileNamed: "HealthMeter") {
            HPMeter.position = CGPoint(x:0, y:50)
            node.addChild(HPMeter)
        }
    }

    override func willRemoveFromEntity() {

    }

    override func update(deltaTime seconds: TimeInterval) {

    }

    override class var supportsSecureCoding: Bool {
        true
    }
}
```

- In GameScene.sks, select the player node. Click the button to show the
inspectors and then switch to the Component Inspector.
- Click the `+` button to reveal the list of available components. Add the 
HealthComponent

{% include figure.liquid path="assets/img/courses/csc496/11-entity-component/health1.png" width="50%" zoomable=true %}


- Test the build. You should see the health bar attached to your player and 
move with the player. 

{% include figure.liquid path="assets/img/courses/csc496/11-entity-component/health2.png" width="50%" zoomable=true %}



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
