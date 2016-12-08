
unsigned char max_array(unsigned int array[], unsigned char tam){
	unsigned char location =0;
	unsigned int maximum = array[0];
	unsigned char c = 0;
  for (c = 1; c < tam; c++)
  {
    if (array[c] > maximum)
    {
       maximum  =(array[c]);
       location = c;
    }
  }
	return location;
}

unsigned char min_array(unsigned int array[], unsigned char tam){
	unsigned char location =0;
	unsigned int minimum = array[0];
	unsigned char c = 0;
  for (c = 1; c < tam; c++)
  {
    if (array[c] < minimum)
    {
       minimum = array[c];
       location = c;
    }
  }
	return location;
}

unsigned int media_array(unsigned int array[], unsigned char tam){

	unsigned char c = 0;
	double valor = 0;
        double multiplicador = (1.0/((double)tam));
  for (c = 0; c < tam; c++)
  {
       valor += ((double)array[c])*multiplicador;
  }
        return (unsigned int)valor;
}


unsigned int somatorio_array(unsigned int array[], unsigned char tam){

	unsigned char c = 0;
	unsigned long int valor = 0;
  for (c = 0; c < tam; c++)
  {
       valor += array[c] ;
  }
        return (unsigned int)valor;
}
