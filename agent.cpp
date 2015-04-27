// *********************************************************************************************
// INTELIGENCIA ARTIFICIAL.
// Solución al problema del Guión de prácticas 2: Agentes Reactivos - El robot trufero
// *********************************************************************************************
// Autor: Pedro Fernández Bosch. E-Mail: pedro@pedrobosch.es
// Departamento de Ciencias de la Computación e Inteligencia Artificial, Universidad de Granada.
// Última modificación: 12/04/2015.
// *********************************************************************************************

#include "agent.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>

using namespace std;

// -----------------------------------------------------------

Agent::ActionType Agent::Think()
{
    // -----------------------------------------------------------
    // IMPRIMIR LOS RESULTADOS DE LA POSICION ACTUAL
    // -----------------------------------------------------------
    iteracion++;                                            // Incrementar el número de iteracion
    
    cout << "ITERACION: " << iteracion << endl;             // Número de la iteracción actual
    cout << "x=" << x << "; y=" << y << endl;               // Posicion relativa de X e Y

    cout << "POSICIONES VECINAS: " << endl;                 // Impresión por pantalla de las posiciones vecinas
    cout << "Arriba: " << matriz[x][((y+9)%10)] << endl;    // Arriba
    cout << "Decha:  " << matriz[((x+1)%10)][y] << endl;    // Derecha
    cout << "Abajo:  " << matriz[x][((y+1)%10)] << endl;    // Abajo
    cout << "Izqda:  " << matriz[((x+9)%10)][y] << endl;    // Izquierda
    cout << endl << "###########################################################" << endl << endl;
    
    // -----------------------------------------------------------
    // ACTUALIZACION
    // -----------------------------------------------------------

    for(int i=0;i<10;i++){                                  // Incrementar el rango de las posiciones mayores que 0 (posiciones que no son obstaculos)
        for(int j=0;j<10;j++){
            if(matriz[i][j]>-1)
                matriz[i][j]++;
        }
    }

    matriz[x][y] = 0;                                       // Actualizar la posición actual a 0 (visitada)

    if(bump_){                                              // Si choca, marca el obstaculo con valor (-1)
        obstaculo_[orientacion_]=true;

        if(orientacion_==0){                        // Arriba
            matriz[x][((y+9)%10)] = -1;
        }
        else if(orientacion_==1){                   // Derecha
            matriz[(x+1)%10][y] = -1;
        }
        else if(orientacion_==2){                   // Abajo
            matriz[x][(y+1)%10] = -1;
        }
        else{                                       // Izquierda
            matriz[(x+9)%10][y] = -1;
        }
    }
    else if(ult_accion_==actTURN_R){                        // Si la última acción fue un giro a la derecha, modificamos la orientación.
        orientacion_= (orientacion_+1)%4;
    }
    else if(ult_accion_==actTURN_L){                        // Si la última acción fue un giro a la izquierda, modificamos la orientación.
        orientacion_= (orientacion_+3)%4;
    }
    else if (ult_accion_==actFORWARD){                      // Si la última acción fue avance, actualizar su posición en la matriz
        if(orientacion_==0){                        // Arriba
            y=((y+9)%10);
        }
        else if(orientacion_==1){                   // Derecha
            x=((x+1)%10);
        }
        else if(orientacion_==2){                   // Abajo
            y=(y+1)%10;
        }
        else{                                       // Izquierda
            x=(x+9)%10;
        }
    }

    // -----------------------------------------------------------
    // DECISION
    // -----------------------------------------------------------

	ActionType accion;                                      // Acción a realizar

    if(trufa_size_>10){                                     // Si en la posición actual detecta mas de 10 trufas, las extrae
        accion=actEXTRACT;
    }
    else if(trufa_size_==-1){                               // Si en la posición actual no conoce cuantas trufas hay, olfatea
        accion=actSNIFF;
    }
    else{                                                   // Si la acción es un movimiento

        // Obtener entre los vecinos Arriba, Derecha, Abajo, Izquierda, el mas adecuado para avanzar
        // Prioridad 1: Una posición que nunca hemos visitado antes
        // Prioridad 2: La posición que hace mas tiempo que hemos visitado

        int vecinos[4];
        vecinos[0] = matriz[x][((y+9)%10)];         // Arriba
        vecinos[1] = matriz[((x+1)%10)][y];         // Derecha
        vecinos[2] = matriz[x][((y+1)%10)];         // Abajo
        vecinos[3] = matriz[((x+9)%10)][y];         // Izquierda

        // Elegir cual es el mejor movimiento comparando el valor de los vecinos
        int movimiento = orientacion_;
        for (int i=0; i<4; ++i){
            if(vecinos[i]>vecinos[movimiento]){
                movimiento = i;
            }
        }

        if (movimiento==orientacion_){              // ¿Hacia dónde voy?
            accion=actFORWARD;
        }
        else if (movimiento==((orientacion_+1)%4)){ // Girar a la derecha
            accion=actTURN_R;
        }
        else{                                       // Girar a la izquierda
            accion = actTURN_L;
        }
    }

    ult_accion_ = accion;                                   // Guardar la última acción realizada en ult_accion_

    return accion;
}

// -----------------------------------------------------------

void Agent::Perceive(const Environment &env)
{
	trufa_size_ = env.TrufaAmount();
	bump_ = env.isJustBump();
}

// -----------------------------------------------------------

string ActionStr(Agent::ActionType accion)
{
	switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actSNIFF: return "SNIFF";
	case Agent::actEXTRACT: return "EXTRACT";
	case Agent::actIDLE: return "IDLE";
	default: return "???";
	}
}
