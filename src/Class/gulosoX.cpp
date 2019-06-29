guloso(){
  if(p == NULL){
    return 0;
  }

  Aresta *a = p->getListaAdjacente();

  //fila que prioriza o menor custo
  FilaPrioridade fila; 

  while(a != NULL)
    adjacente.insere(a);
  
  for(int i = 0; i < p->getGrau(); i++){
    if(nosLidos.push_back(fila.getPrimeiro()))
      fila.removeInicio();
    else{
      resultado.
    }
  }
}
