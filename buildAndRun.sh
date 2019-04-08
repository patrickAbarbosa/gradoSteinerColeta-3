#!/bin/bash
echo "Criando Build..."
g++ main.cpp src/Class/* src/Headers/* -o Teste

echo "--- Run Build ---"
./Teste