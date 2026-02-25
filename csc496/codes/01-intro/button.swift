struct ContentView: View {
    @State private var showDetails = false
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
                    
        if showDetails {
            Text("Good jobs!!!").bold()
        }
    }
}