#!/bin/bash
echo "Criando Build..."
g++ main.cpp src/Class/* src/Headers/* -o Teste

echo "--- Run Build ---"
./Teste k400.3.con.red

echo "--- End Build ---"