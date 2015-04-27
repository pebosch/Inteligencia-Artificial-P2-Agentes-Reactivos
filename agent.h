// *********************************************************************************************
// INTELIGENCIA ARTIFICIAL.
// Solución al problema del Guión de prácticas 2: Agentes Reactivos - El robot trufero
// *********************************************************************************************
// Autor: Pedro Fernández Bosch. E-Mail: pedro@pedrobosch.es
// Departamento de Ciencias de la Computación e Inteligencia Artificial, Universidad de Granada.
// Última modificación: 12/04/2015.
// *********************************************************************************************

#ifndef AGENT__
#define AGENT__

#include <string>

using namespace std;

// -----------------------------------------------------------
// CLASS AGENT
// -----------------------------------------------------------
class Environment;
class Agent
{
public:
	Agent(){
        trufa_size_=-1;
        bump_=false;
        orientacion_=0;
        for(int i=0; i<4; i++)
            obstaculo_[i]=false;
        ult_accion_ = actIDLE;

        iteracion=0;                // Inicializar el número de iteración=0
        x=0; y=0;                   // Inicializar la posición actual en x=0 e y=0

        for(int i=0;i<10;i++){      // Inicializar todas las posiciones de la matriz a 1000
            for(int j=0; j<10; j++)
                matriz[i][j]=1000;
        }
	}

	enum ActionType
	{
	    actFORWARD,
	    actTURN_L,
	    actTURN_R,
	    actSNIFF,
	    actEXTRACT,
	    actIDLE
	};

	void Perceive(const Environment &env);
	ActionType Think();
private:
	int trufa_size_;
	bool bump_;

    int orientacion_;           // Variable que almacena la orientación actual del robot (0=Arriba, 1=Derecha, 2=Abajo, 3=Izquierda).
    bool obstaculo_[4];         // Variable para indicar dónde hay un obstaculo

    int iteracion;              // Almacena la iteración actual para mostrarla por pantalla
    int matriz[10][10];         // Matriz de posiciones 10x10 (Representación de mundo cuadriculado)
    int x, y;                   // Posición actual del robot

    ActionType ult_accion_;
};

string ActionStr(Agent::ActionType);

#endif
