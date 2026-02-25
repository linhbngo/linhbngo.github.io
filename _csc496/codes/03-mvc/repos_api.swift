//
//  repos_api.swift
//  repo_list
//
//  Created by Linh Ngo on 1/24/25.
//

import Foundation

class RepoService {
    private let url = URL(string: "https://api.github.com/users/linhbngo/repos?page=1&per_page=200")!
    
    func fetchRepos(completion: @escaping (Result<[Repo], Error>) -> Void) {
        URLSession.shared.dataTask(with: url) { data, response, error in
            if let error = error {
                completion(.failure(error))
                return
            }
            
            guard let data = data else {
                completion(.failure(NSError(domain: "", code: -1, userInfo: [NSLocalizedDescriptionKey: "No data"])))
                return
            }
            
            do {
                let repos = try JSONDecoder().decode([Repo].self, from: data)
                completion(.success(repos))
            } catch {
                completion(.failure(error))
            }
        }.resume()
    }
}
