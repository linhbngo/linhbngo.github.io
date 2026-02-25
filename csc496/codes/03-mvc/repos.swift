//
//  repos.swift
//  repo_list
//
//  Created by Linh Ngo on 1/24/25.
//

import Foundation

class RepoController: ObservableObject {
    @Published var repos: [Repo] = []
    @Published var isLoading: Bool = false
    @Published var errorMessage: String? = nil
    
    private let userService = RepoService()
    
    func fetchRepos() {
        isLoading = true
        errorMessage = nil
        
        userService.fetchRepos { [weak self] result in
            DispatchQueue.main.async {
                self?.isLoading = false
                switch result {
                case .success(let repos):
                    self?.repos = repos
                case .failure(let error):
                    self?.errorMessage = error.localizedDescription
                }
            }
        }
    }
}
