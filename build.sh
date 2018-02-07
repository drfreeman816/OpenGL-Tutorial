#!/bin/bash

# OpenGL tutorial

# Colors
echo_black() { echo "$(tput setaf 0)$*$(tput setaf 7)"; }
echo_darkred() { echo "$(tput setaf 1)$*$(tput setaf 7)"; }
echo_green() { echo "$(tput setaf 2)$*$(tput setaf 7)"; }
echo_yellow() { echo "$(tput setaf 3)$*$(tput setaf 7)"; }
echo_purple() { echo "$(tput setaf 4)$*$(tput setaf 7)"; }
echo_pink() { echo "$(tput setaf 5)$*$(tput setaf 7)"; }
echo_cyan() { echo "$(tput setaf 6)$*$(tput setaf 7)"; }
echo_white() { echo "$(tput setaf 7)$*$(tput setaf 7)"; }
echo_grey() { echo "$(tput setaf 8)$*$(tput setaf 7)"; }
echo_red() { echo "$(tput setaf 9)$*$(tput setaf 7)"; }

# Select parameters
program="$1"
library="myOpenGL"

# Libraries used
libs="-lglfw -lGLEW -lGL"

clear

echo_yellow "Compiling $program"

# Create directories
printf '\n'
echo_purple "Creating directories..."
rm -r obj lib bin
mkdir -p obj lib bin

# Compile headers
printf '\n'
echo_purple "Detecting headers..."
headers=./inc/*.h
sources=""
for header in $headers
do
  file=${header##*/}
  file=${file%.*}

  printf '\n'
  echo_cyan "$file"

  sources="$sources ./src/$file.cpp"

done

#printf '\n'
#echo_green "$sources"

# Compile program and link
printf '\n'
echo_purple "Compiling $program..."
time g++ ./src/$program.cpp $sources -Wall $libs -I ./inc -o ./bin/$program

# Run test program
printf '\n'
echo_purple "Running $program..."
printf '\n'
  time optirun ./bin/$program

printf '\n'
