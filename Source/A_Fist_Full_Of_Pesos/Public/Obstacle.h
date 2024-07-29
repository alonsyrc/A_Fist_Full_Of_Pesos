// Completa tu aviso de copyright en la página de Descripción de la Configuración del Proyecto.

#pragma once // Asegura que este archivo de encabezado solo se incluya una vez durante la compilación.

#include "CoreMinimal.h" // Incluye los componentes esenciales del motor de Unreal.
#include "GameFramework/Actor.h" // Incluye la clase base AActor.
#include "Obstacle.generated.h" // Genera el código necesario para la clase AObstacle.

/**
 * Clase AObstacle que hereda de AActor.
 */
UCLASS() // Macro que indica que esta es una clase de Unreal Engine.
class  AObstacle : public AActor
{
	GENERATED_BODY() // Macro que genera el código estándar necesario para las clases de Unreal Engine.

public:
	// Establece los valores predeterminados para las propiedades de este actor.
	AObstacle();

protected:
	// Llamada cuando el juego comienza o cuando el actor es generado.
	virtual void BeginPlay() override;

public:
	// Llamada cada cuadro.
	virtual void Tick(float DeltaTime) override;
};
