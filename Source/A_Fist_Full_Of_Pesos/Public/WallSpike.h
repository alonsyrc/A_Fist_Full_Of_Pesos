// Fill out your copyright notice in the Description page of Project Settings.
// Completa tu aviso de copyright en la página de Descripción de la Configuración del Proyecto.

#pragma once

// Incluye los archivos de encabezado esenciales del motor de Unreal.
#include "CoreMinimal.h"
// Incluye el encabezado de la clase base ASpikes.
#include "Spikes.h"
// Genera el código necesario para la clase AWallSpike.
#include "WallSpike.generated.h"

/**
 * Clase AWallSpike que hereda de ASpikes.
 */
UCLASS() // Macro que indica que esta es una clase de Unreal Engine.
class A_FIST_FULL_OF_PESOS_API AWallSpike : public ASpikes
{
	GENERATED_BODY() // Macro que genera el código estándar necesario para las clases de Unreal Engine.

public:
	// Constructor de la clase AWallSpike.
	AWallSpike();

protected:
	// Función que se llama cuando el juego comienza o cuando se genera el objeto.
	virtual void BeginPlay() override;

public:
	// Función que se llama cada cuadro del juego.
	virtual void Tick(float DeltaTime) override;

};
