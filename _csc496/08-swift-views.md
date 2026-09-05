---
layout: lecture
pretty_table: true
collection: csc496
title: "Views and 3rd Party Library"
toc:
  - name: Views
  - name: Third Party Library
---
# Views and 3rd Party Library

## Views

{% details New SwiftUI View %}

- To create a new view in SwiftUI, you start by importing the SwiftUI
package and then defining a new struct that conforms to the **View**
protocol.
- Inside the struct, you'll implement the body computed property, which
describes the view's content and layout.
- Here's a basic example to demonstrate creating a new view in SwiftUI:

```swift
import SwiftUI
struct MyNewView: View {
    var body: some View {
        Text("Hello, world!")
            .padding()
    }
}
```

{% enddetails %}
{% details Breakdown of New SwiftUI View %}

- Define a New Struct: Create a new Swift struct and make it conform to the View
protocol.

```swift
import SwiftUI
struct MyNewView: View {
```

- Implement the Body: Within the struct, you'll need to implement a body
computed property. This is where you define what your view looks like.

```swift
var body: some View {
    Text("Hello, world!")
        .padding()
}
```

- To use MyNewView inside another view, you would do the followings:

```swift
struct ContentView: View {
    var body: some View {
        MyNewView()
    }
}
```

{% enddetails %}
{% details Structuring Views %}


- In SwiftUI, it's a good practice to structure your views by breaking
them down into smaller, reusable components.
- For example, suppose you have a view that displays user
information. This view could consist of smaller views: 
    - one for the user's avatar, 
    - one for the username, 
    - and one for the user's bio.

- Create a new project called `views` that implements the above example 
with the following contents.
    - `viewsApp`

    ```swift
    import SwiftUI

    @main
    struct viewsApp: App {
        var body: some Scene {
            WindowGroup {
                ContentView()
            }
        }
    }
    ``` 

    - `ContentView`

    ```swift
    import SwiftUI

    struct ContentView: View {
        @State private var showProfile = false

        var body: some View {
            if showProfile {
                UserProfileView()
                Button("Back") {
                    showProfile = false
                }
            } else {
                Button("Profile") {
                    showProfile = true
                }
            }
        }
    }
    #Preview {
        ContentView()
    }
    ```

    - `Views`

    ```swift
    import SwiftUI

    struct UserProfileView: View {
        var body: some View {
            VStack {
                UserAvatarView()
                UserNameView()
                UserBioView()
            }
        }
    }

    struct UserAvatarView: View {
        var body: some View {
            Image(systemName: "person.circle.fill")
                .resizable()
                .frame(width: 100, height: 100)
        }
    }

    struct UserNameView: View {
        var body: some View {
            Text("Golden Rams")
                .font(.title)
        }
    }

    struct UserBioView: View {
        var body: some View {
            Text("I love SwiftUI!")
                .font(.subheadline)
        }
    }
    ```


{% enddetails %}
{% details NavigationView %}

- You can wrap your views in other framework, for example, `NavigationView`. 
- Try modifying `ContentView` with the following:

```swift
struct ContentView: View {
    @State private var showProfile = false

    var body: some View {
        NavigationView {
            if showProfile {
                UserProfileView()
                    .navigationBarTitle("User Profile", displayMode: .inline)
                    .navigationBarItems(trailing: Button("Back") {
                        showProfile = false
                    })
            } else {
                Button("Profile") {
                    showProfile = true
                }
            }
        }
    }
}
```

{% enddetails %}
## Third Party Library

{% details Adding third party packages %}


{% include figure.liquid path="assets/img/courses/csc496/08-views/addpkg.png" max-width="50%" zoomable=true %}

- Enter the GitHub URL of the 3rd party library into the search box

{% include figure.liquid path="assets/img/courses/csc496/08-views/addpkg2.png" max-width="50%" zoomable=true %}

- Press `Add Package`

{% enddetails %}
{% details Example: Kingfisher %}


- [https://github.com/onevcat/Kingfisher](https://github.com/onevcat/Kingfisher)
- Modify `Views`:

```swift
import Kingfisher

struct UserAvatarView: View {
    var body: some View {
        KFImage(URL(string: "https://www.wcupa.edu/communications/images/goldenRamLogo.png"))
            .resizable()
            .frame(width: 100, height: 100)
    }
}
```

{% enddetails %}
{% details Example: ConfettiSwiftUI %}

- [https://github.com/simibac/ConfettiSwiftUI](https://github.com/simibac/ConfettiSwiftUI)

- Modify `Views`:

```swift
import ConfettiSwiftUI

struct UserAvatarView: View {
    @State private var trigger: Int = 0
    var body: some View {
        KFImage(URL(string: "https://www.wcupa.edu/communications/images/goldenRamLogo.png"))
            .resizable()
            .frame(width: 100, height: 100)
        Button("Cheers!!!") {
            trigger += 1
        }
        .confettiCannon(trigger: $trigger)
    }
}
```

{% enddetails %}
{% details Hands-on: Subsonic %}


- [https://github.com/twostraws/Subsonic](https://github.com/twostraws/Subsonic)
- Add the ability to play a sound when clicking the `Profile` button
    - [Library of free sample mp3 sounds](https://citizen-dj.labs.loc.gov/loc-fma/use/)
    - [Royalty Free Sounds Effects Archive](https://sonniss.com/gameaudiogdc/#:~:text=Royalty%20Free%20Sound%20Effects%20Archive,same%20files%20as%20we%20sell.)
    - [https://freesound.org/](https://freesound.org/)
    - [Other resources](https://blog.felgo.com/game-resources/free-music-for-games#:~:text=ZapSplat%20offers%20an%20easy%2Dto%2Dbrowse%20library%20of%20royalty,free%20sound%20effects%20for%20you%20to%20use.)
- Add the ability to automatically play a theme when the Golden Ram profile appears!





{% enddetails %}
