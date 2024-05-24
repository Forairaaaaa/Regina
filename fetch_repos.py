import os
import subprocess
import json


def clone_or_update_repo(repo_url, path, branch):
    command = []
    command.append('git')
    command.append('clone')
    
    if branch:
        command.append('-b')
        command.append(branch)

    command.append(repo_url)
    command.append(path)

    subprocess.run(command)

def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    config_path = os.path.join(script_dir, 'repos.json')

    with open(config_path) as f:
        repos = json.load(f)

    for repo in repos:
        repo_path = os.path.join(script_dir, repo['path'])
        branch = repo.get('branch')
        clone_or_update_repo(repo['url'], repo_path, branch)


if __name__ == "__main__":
    print("start fetching dependent repos..")
    main()
