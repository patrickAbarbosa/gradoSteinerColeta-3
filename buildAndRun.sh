#!/bin/bash
echo "Criando Build..."
g++ main.cpp src/Class/* src/Headers/* -o grafosGrupo3

echo "--- Run Build ---"
./grafosGrupo3 K400.3.con.red

echo "--- End Build ---"

echo "remove file executavel"
rm grafosGrupo3

echo "remove files" 
rm GrafoPNG.dot
rm GrafoPNG.dot.png
