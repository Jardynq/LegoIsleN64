# How to build
1. Own a legitemate installation of Lego Island.
2. In the game installation folder you should find a folder called `LEGO`.   
Copy the contents of this folder (`scripts` and `data`) into the `assets` folder in project root.   
After copying, the `assets` folder should contain 3 subfolder: `cursors`, `data`, `scripts`.
3. Install docker.
5. (Optional) Ensure the `user`, `UID` and `GID` fields in `docker-compose.yml` point to your user and group.  
You can get your user with `id -u` and group with `id -g`. 
4. Execute `docker compose up -d` in project root.
5. Enter a shell in the newly created docker instance and run `make`. 
6. The output is called `isle.z64` and is located in project root.

# How to run
1. Download the emulator `Ares`. 
2. In `Ares` open `isle.z64`

# How to setup vscode
1. Install `Dev Containers` vscode extension
2. Attach vscode to the newly created docker container (see "How to Build" section) in the sidebar 
3. Install the `clangd` extension in the newly attached vscode instance
