#ifndef NEURON_H
#define NEURON_H

//AUTHOR : HAMORA HADI

class Neuron{
//what does the Neuron do??
//Its Principle is not that difficult:
//It gets maxI Inputs(I will call them xI) and multiplies each of them with a wheight (wI)
//so first Input*first wheight and so on....
//After that it just sums all of this products up
//These sum is put in the activations function
 //in this Neural Network the activation function is the sigmoid function, but there are many of them
//The result of this function is called activation of this Neuron


//sigmoid function:
//sigmoid function gives an result between 0 and 1:
 //sigmoid(-infinity)=0
 //sigmoid(infinity)=1
 //sigmoid(0)=0.5



//Lets take some example:
 //The Inputs could be coordinates in an 2-Dimensional room (2 Inputs:x=3,y=2)
 //The wheights could be 1 and -1
 //The output could be the suggested colour of the point: 0 for blue and 1 for red
 //So what the Neuron is doing is just calculating: sum=x*1+y*-1=x-y and putting this into sigmoid function, so if x-y>0 then this Neuron suggests the point to be more like red, otherwise more like blue....
 //So it ould be like this:
 //rrrrrr
 //brrrrr
 //bbrrrr
 //bbbrrr
 //bbbbrr
 //bbbbbr
 //bbbbbb
 
//But what if P(3,2) is blue??//Thie means that the wheights are probably wrong
//And this is what the learn() does: It tries to improve the wheights!
//For this it needs altleast a pair of inputs and the mistake it has made(correctOutput-output)...
//Then it changes every wheight a little bit to improve the output:
//(wheight I)+="Learnrate"*mistake*(Input I)  for every wheight
//if the mistake is positive the wheight and through this the resulted output will be incresed, otherwise decreased, so after the learning proccess the data fits better...
//"Learnrate" steers how much the wheights are changed, too much changing is bad
//(imagine the Neuron is perfect trained, only one point does not fit and destroys all well-trained wheights)
//Why do we multiply with mistake and Input I??
//We multiply with mistake for the same reason as there is a Learnrate, the better the output already is the more we want to leave it as it is
//We multiply with Input I, because the higher Input I is the higher is the effect of changing the wheight, for example we dont want to change a wheight with input 0, because this would not improve the output
 	



	private:
		double *wI;
		int maxI;
		double activation;
	
	public:
		Neuron();
		virtual ~Neuron();
		
		void initialize(int n);
		
		void calc(double* xI);
		void calc(int* xI);
		
		void learn(double Fehler, double *xI);
		void learn(double Fehler, int *xI);
		
		double getactivation();
		double* getwI();


	protected:


};

#endif // NEURON_H

#include "stdlib.h"
#include <iostream>
#include <math.h>


Neuron::Neuron()
{}
Neuron::~Neuron()
{}

void Neuron::initialize(int n){//initializes the Neuron
	maxI=n;					 //with n inputs
	wI=new double[n+1];		   //BIAS
	for(int i=0;i<n;i++)		
		wI[i]=double(rand()%20-10)/10;			  
}

void Neuron::calc(double *xI)   {
	double sum=0;			   
	for(int i=0;i<maxI;i++)	 
		sum+=xI[i]*wI[i];	   
		sum+=wI[maxI]*1;	
	activation=1/(1+pow( 2.718281828459,(-sum)));
}

void Neuron::calc(int *xI)	  {
	double sum=wI[maxI];		
	for(int i=0;i<maxI;i++)
		sum+=double(xI[i])*wI[i]; 
	activation=1/(1+pow(2.718281828459,(-sum)));
}

double Neuron::getactivation() {
	return activation;//returns the activation from the Neuron
}

void Neuron::learn(double mistakes,double *xI){	//learns with the mistakes and the inputs
	for(int i=0;i<maxI;i++)
		wI[i]+=(activation)*(1-activation)*0.5*mistakes*xI[i];	//every weight is increased by "Learnrate"*mistake*input
	wI[maxI]+=(activation)*(1-activation)*0.5*mistakes*1; //here the bias is trained
	
}

void Neuron::learn(double Fehler,int *xI){//the same as up just with integers
	for(int i=0;i<maxI;i++){
		wI[i]+=(activation)*(1-activation)*0.01*Fehler*double(xI[i]);	   //converts the integers into doubles
	}
	wI[maxI]+=(activation)*(1-activation)*0.5*Fehler;
}

double* Neuron::getwI(){ //returns weights
	return wI;
}

#ifndef Layer_H
#define Layer_H

class Layer{
	public:
		Layer();
		void initialize(int nN, int nxI);
		virtual ~Layer();
		void calc(double *xI);
		void calc(int *xI);
		double *getactivations();
		int getnneurons();
		void learn(double* Fehler,double* xI);
		void learn(double* Fehler,int* xI);
		double** getwIs();

	protected:

	private:
		Neuron *neurons;
		int nneurons;
		double *activations;
};

#endif // Layer_H

#include <iostream>

Layer::Layer(){ }

Layer::~Layer()
{
	//dtor
}

void Layer::initialize(int nN, int nxI){
	nneurons=nN;						//saves the number of the Neurons
	neurons=new Neuron[nN];			 //constructs the Neurons
	for(int i=0;i<nN;i++)			   //every Neuron
		neurons[i].initialize(nxI);	 //is initialized
	activations=new double[nN];		 //the activations are declared
}

void Layer::calc(double* xI){//calcs all Neurons of the layer with the inputs
	for (int i=0;i<nneurons;i++){//every Neurons
		neurons[i].calc(xI);						//calcs
		activations[i]=neurons[i].getactivation();	  //and the result is stored in the activations array
	}
}

void Layer::calc(int* xI){	//the same as up with integers
	for (int i=0;i<nneurons;i++){
		neurons[i].calc(xI);
		activations[i]=neurons[i].getactivation();
	}
}

double* Layer::getactivations(){	 //returns an pointer to the activations
	return activations;
}

int Layer::getnneurons(){	//returns the number of Neurons in this layer
	return nneurons;
}

void Layer::learn(double* Fehler, double* xI){//the Layer and its Neurons learn with the
	for(int i=0;i<nneurons;i++)				 //all Neurons
		neurons[i].learn(Fehler[i],xI);		 //learn methode
}

void Layer::learn(double* Fehler, int* xI){
	for(int i=0;i<nneurons;i++)
		neurons[i].learn(Fehler[i],xI);
}

double** Layer::getwIs(){
	double** res =new double*[nneurons];
	for(int i=0;i<nneurons;i++)
		res[i]=neurons[i].getwI();
	return res;
}

#ifndef NETWORK_H
#define NETWORK_H

class Network{
	public:
		Network(int nL, int nN, int nXi);
		virtual ~Network();
		void calc(double inputs[]);
		void learn(double *outputs, double inputs[]);
		double *getoutput();
		void status();

	protected:

	private:
		Layer *layers;
		int nLayer;
		int nNeurons;
		double *activations[];
};

#endif // NETWORK_H

#include <iostream>

Network::Network(int nL, int nN, int nXi){
	nNeurons=nN;
	nLayer=nL;
	layers= new Layer[nL];
	for(int i=0; i<nL;i++){
		layers[i].initialize(nN,nXi);
		activations[i] = new double[3*nN];
		activations[i] = &activations[i][2*nN];
	}
}

Network::~Network(){ }

void Network::calc(double *inputs){
	layers[0].calc(inputs);
	activations[0]=layers[0].getactivations();
	for(int i=1;i<nLayer;i++){
		layers[i].calc(activations[i-1]);
		activations[i]=layers[i].getactivations();
	}
}



void Network::learn(double *outputs,double inputs[]){
	double *Fehler=new double[nNeurons];

	for(int i=0;i<nNeurons;i++)
		Fehler[i]=double(outputs[i])-double(activations[nLayer-1][i]);
	double *Fehler2=new double[nNeurons];
	for(int i=nLayer-1;i>0;i--){
		layers[i].learn(Fehler,activations[i-1]);
		for(int j=0;j<nNeurons;j++){
			Fehler2[j]=Fehler[j];
			Fehler[j]=0;
		}
		for(int j=0;j<nNeurons;j++){
			for(int k=0;k<nNeurons;k++)
				Fehler[j]+=(Fehler2[k]*layers[i].getwIs()[k][j]);
		}
	}
	layers[0].learn(Fehler,inputs);
}

double* Network::getoutput(){
	return activations[nLayer-1];
}

void Network::status(){
	for(int i=0;i<nLayer;i++){
		for(int j=0;j<nNeurons;j++){
			for(int k=0;k<nNeurons+1;k++)
				std::cout<< layers[i].getwIs()[j][k] << "  ";
			std::cout << "\n";
		}
		std::cout << "\n"<< "\n"<< "\n";
	}
}

#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

int main(){
	//In the main function, the number of neural network can be edited by you
	int nN=3;
	double *inputs= new double[nN];
	srand(time(0));
	double *n=new double[nN];
	double *outputdesired= new double[nN];

	inputs[0]=1;
	inputs[1]=1;
	inputs[2]=1;

	//4 Layers
	Network network(4,nN,nN);
	double *output= new double[nN];
	srand(time(0));
	network.calc(inputs);
	outputdesired[0]=0;
	outputdesired[1]=0;
	outputdesired[2]=1;
	for(int j=0;j<1;j++){
		for(int i=0;i<5000;i++){
	
			network.learn(outputdesired,inputs);
			inputs[0]=i%2;
			inputs[1]=((i-(i%2))/2)%2;
			inputs[2]=((((i-(i%2))/2)-((i-(i%2))/2)%2)/2)%2;
			network.calc(inputs);
			outputdesired[0]=0;
			outputdesired[1]=0;
			outputdesired[2]=0;
			if(inputs[0]&&inputs[1]&&inputs[2])
				outputdesired[2]=1;
			else if((inputs[0]&&(inputs[1]||inputs[2]))||(inputs[1]&&inputs[2]))
				outputdesired[1]=1;
			else if(inputs[0]||inputs[1]||inputs[2])
				outputdesired[0]=1;
		}
	}
	
	inputs[0]=0;
	inputs[1]=0;
	inputs[2]=0;
	network.calc(inputs);
	cout << inputs[0]<<"  "<< inputs[1]<<"  "<< inputs[2]<<"  "<< endl;
	output=network.getoutput();
	for(int i=0;i<nN;i++)
		cout << output[i] << "  ";
	cout << "\n\n";
	
	inputs[0]=0;
	inputs[1]=0;
	inputs[2]=1;
	network.calc(inputs);
	cout << inputs[0]<<"  "<< inputs[1]<<"  "<< inputs[2]<<"  "<< endl;
	output=network.getoutput();
	for(int i=0;i<nN;i++)
		cout << output[i] << "  ";
	cout << "\n\n";
	
	inputs[0]=0;
	inputs[1]=1;
	inputs[2]=0;
	network.calc(inputs);
	cout << inputs[0]<<"  "<< inputs[1]<<"  "<< inputs[2]<<"  "<< endl;
	output=network.getoutput();
	for(int i=0;i<nN;i++)
		cout << output[i] << "  ";
	cout << "\n\n";
	
	inputs[0]=1;
	inputs[1]=0;
	inputs[2]=0;
	network.calc(inputs);
	cout << inputs[0]<<"  "<< inputs[1]<<"  "<< inputs[2]<<"  "<< endl;
	output=network.getoutput();
	for(int i=0;i<nN;i++)
		cout << output[i] << "  ";
	cout << "\n\n";
	   
	
	inputs[0]=1;
	inputs[1]=1;
	inputs[2]=0;
	network.calc(inputs);
	cout << inputs[0]<<"  "<< inputs[1]<<"  "<< inputs[2]<<"  "<< endl;
	output=network.getoutput();
	for(int i=0;i<nN;i++)
		cout << output[i] << "  ";
	cout << "\n\n";
	
	inputs[0]=1;
	inputs[1]=0;
	inputs[2]=1;
	network.calc(inputs);
	cout << inputs[0]<<"  "<< inputs[1]<<"  "<< inputs[2]<<"  "<< endl;
	output=network.getoutput();
	for(int i=0;i<nN;i++)
		cout << output[i] << "  ";
	cout << "\n\n";
	
	inputs[0]=0;
	inputs[1]=1;
	inputs[2]=1;
	network.calc(inputs);
	cout << inputs[0]<<"  "<< inputs[1]<<"  "<< inputs[2]<<"  "<< endl;
	output=network.getoutput();
	for(int i=0;i<nN;i++)
		cout << output[i] << "  ";
	cout << "\n\n";
	
	inputs[0]=1;
	inputs[1]=1;
	inputs[2]=1;
	network.calc(inputs);
	cout << inputs[0]<<"  "<< inputs[1]<<"  "<< inputs[2]<<"  "<< endl;
	output=network.getoutput();
	for(int i=0;i<nN;i++)
		cout << output[i] << "  ";
	cout << "\n\n";
	
	cout << inputs[0]<<"  "<< inputs[1]<<"  "<< inputs[2]<<"  "<< endl;
	output=network.getoutput();
	for(int i=0;i<nN;i++)
		cout << output[i] << "  ";
	cout << "\n\n";
	network.status();

	return 0;
}
