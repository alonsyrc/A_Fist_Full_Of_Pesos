// Completa tu aviso de copyright en la p�gina de Descripci�n de la Configuraci�n del Proyecto.

#pragma once

#include "CoreMinimal.h" // Incluye las definiciones b�sicas de Core.
#include "GameFramework/Actor.h" // Incluye la clase base AActor.
#include "BaseLevel.generated.h" // Genera el c�digo necesario para la clase.

class UBoxComponent; // Declaraci�n anticipada de UBoxComponent.

UCLASS()
class A_FIST_FULL_OF_PESOS_API ABaseLevel : public AActor // Define la clase ABaseLevel que hereda de AActor.
{
	GENERATED_BODY() // Macro que genera el c�digo necesario para la clase.

public:
	// Establece valores predeterminados para las propiedades de este actor.
	ABaseLevel();

protected:
	// Llamado cuando el juego comienza o cuando el actor es generado.
	virtual void BeginPlay() override;

public:
	// Llamado cada cuadro.
	virtual void Tick(float DeltaTime) override;

protected:
	// Componente de colisi�n que act�a como disparador.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Triggers")
		UBoxComponent* Trigger;

	// Componente de colisi�n que indica la ubicaci�n de generaci�n.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Triggers")
		UBoxComponent* SpawnLocation;

public:
	// Devuelve el componente de disparador.
	UBoxComponent* GetTrigger();

	// Devuelve el componente de ubicaci�n de generaci�n.
	UBoxComponent* GetSpawnLocation();
};
