[![Build Status](https://magnum.travis-ci.com/Minecraft-France/Serveur.svg?token=htYEgJf9D1vD8Lyz4aKb&branch=master)](https://magnum.travis-ci.com/Minecraft-France/Serveur)

### Installation
Nous utilisons CMake, donc il suffit de quelques commandes :
```
mkdir bin
cd bin
cmake -G <generator> ..
```
Vous pouvez utiliser (entre autres) les valeurs suivantes pour le `generator`:
* `"CodeBlocks - Unix Makefiles"` pour un projet Code::Blocks sous Linux ;
* `"Xcode"` pour un projet Xcode ;
* `"Unix Makefiles"` pour des classiques Unix Makefiles.
