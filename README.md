# C - Simple Shell

![](https://media.licdn.com/dms/image/C5612AQFpOkcCsn93wg/article-cover_image-shrink_600_2000/0/1618578265410?e=2147483647&v=beta&t=qT6ByTN7vsoPj3aKF6XNy3F4Oc46v6BK4HxCP4g2kXY)

## Table of Contents

- [Description](#description) 
- [Flowchart](#flowchart)
- [Requirements](#requirements)
- [Usage](#usage)
- [Examples](#examples)
- [Description files](#description-files)
- [Contributors](#contributors)

## Description

+ `hsh` is a basic shell made in C. It does execute simple commands with arguments such as `ls -la`, `pwd`, `cat`, etc. 
+ For this project we will use (some of) this functions and systems calls:

### *Function calls*

`closedir` `exit` `fflush` `free` `getcwd` `getline` `getpid` `isatty` `kill` `malloc`  `opendir` `perror` `printf` `fprintf` `vfprintf` `sprintf` `putchar` `read` `readdir` `strtok`

### *System calls*


| fork  |  access | chdir | close | exceve |
| ------------ | ------------ | ------------ | ------------ | ------------ |
| *_exit* | *getpid* | *open* | *signal* | *wait* |
| *waitpid* | *wait3* | *wait4* | *write* | *read* |

## Flowchart

![](https://i.ibb.co/ZSFkx9W/flowchart.jpg)

## Requirements
To compile hsh you need to intall these tools:
+ `gcc` - For Linux check [this](https://gcc.gnu.org/install/) and for windows check [this](https://www.digitalocean.com/community/tutorials/c-compiler-windows-gcc) 

## Usage

To use this function, 
+ first clone the repository:
```bash
git clone https://github.com/Ghelder/holbertonschool-simple_shell.git
```
 
+ go into directory you've clone with `cd`: 
```bash 
cd ./holbertonschool-simple_shell/ 
```
+ then compile the code with `gcc` and some flags: 
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Examples

### *Interactive mode*
+ To enter in interactive mode you have to execute the binary file `hsh` as shown is the image below:

 ![](https://res.cloudinary.com/djvwjnzxw/image/upload/v1682350222/interactive_mode_pkyshj.png)

 ![](https://i.ibb.co/hmq6Nk8/ls-2.png)

### *Non-interactive mode*

```bash
echo "/bin/ls" | ./hsh
```
```bash
echo "pwd" | ./hsh
```
```bash
echo "ls -la /tmp" | ./hsh
```
```bash
echo "env" | ./hsh
```
## Description files

| file | description |
| ------------ | ------------ |
| *main.c* | The main function that runs our shell |
| *main.h* | All prototypes and includes|
| *tokenizer.c* | Make our input and path into tokens to work with |
| *functions_stds.c* | Support functions to use in other functions |
| *checks.c* | Validate if a command exists |

## Contributors
+ Josue Cerrón [@xiayudev](https://github.com/xiayudev)
+ Oscar Salinas [@oscarsa3](https://github.com/Oscarsa3)
+ Helder Guevara [@Ghelder](https://github.com/Ghelder)
+ Alejandro Navarro [@Royalito](https://github.com/Royalito)
