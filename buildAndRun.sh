#!/bin/bash
echo "Criando Build..."
g++ main.cpp src/Class/* src/Headers/* -o Teste

echo "--- Run Build ---"
./Teste K400.3.con.red

echo "--- End Build ---"