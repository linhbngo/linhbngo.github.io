struct ContentView: View {
    @State private var showDetails = false
    @State private var pokemonID = "1"
    var body: some View {
        VStack {
            Image(systemName: "globe")
                .imageScale(.large)
                .foregroundStyle(.tint)
            Text("Hello, world!")
        }
        .padding()
        Button("Show details") {
            showDetails.toggle()
        }
        .padding()
        
        TextField("Pokemon ID", text: $pokemonID).multilineTextAlignment(.center)
        
        if showDetails {
            Image(pokemonID)
            Text("Good jobs!!!").bold()
        }
    }
}
