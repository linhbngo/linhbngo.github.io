//
//  ContentView.swift
//  repo_list
//
//  Created by Linh Ngo on 1/24/25.
//

import SwiftUI

struct Repo: Identifiable,Codable {
    let id: Int
    let name: String
    let full_name: String
}

struct RepoListView: View {
    @ObservedObject var controller = RepoController()
    
    var body: some View {
        NavigationView {
            Group {
                if controller.isLoading {
                    ProgressView("Loading repository...")
                } else if let errorMessage = controller.errorMessage {
                    Text(errorMessage)
                        .foregroundColor(.red)
                        .multilineTextAlignment(.center)
                } else {
                    List(controller.repos) { repo in
                        NavigationLink(destination: RepoDetailView(repo: repo)) {
                            Text(repo.name)
                        }
                    }
                }
            }
            .navigationTitle("Repositories")
            .onAppear {
                controller.fetchRepos()
            }
        }
    }
}

struct RepoDetailView: View {
    let repo: Repo
    
    var body: some View {
        VStack(alignment: .leading, spacing: 16) {
            Text("Repository Name: \(repo.name)")
            Text("Full Repository Name: \(repo.full_name)")
            Spacer()
        }
        .padding()
        .navigationTitle(repo.name)
    }
}

struct RepoListView_Previews: PreviewProvider {
    static var previews: some View {
        RepoListView()
    }
}

struct UserDetailView_Previews: PreviewProvider {
    static var previews: some View {
        RepoDetailView(repo: Repo(id: 1, name: "repository", full_name: "developer/repository"))
    }
}
